#pragma once

#include "logger/logger.hpp"
#include "messaging/publisher.hpp"
#include "timer/timer.hpp"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

constexpr double SIM_RATE = 1.0;

class BoostEvent : public boost::noncopyable {
public:
  BoostEvent(boost::asio::io_service &io_service, int offset_interval, bool periodic, int interval,
             std::function<void(void)> task)
      : m_task(std::move(task)), m_offsetInterval(offset_interval), m_periodic(periodic), m_interval(interval),
        m_timer(io_service) {
    // Schedule start to be ran by the io_service
    io_service.post([this] { start(); });
  }

  ~BoostEvent() { std::cout << "Event destroyed" << std::endl; }

  void execute(boost::system::error_code const &ec) {
    if (!ec) {
      if (this->m_periodic) {
        // timer.expires_at(timer.expires_at() + boost::posix_time::milliseconds(this->interval));
        m_timer.expires_at(m_timer.expires_at() +
                           boost::posix_time::milliseconds(static_cast<int>(this->m_interval / SIM_RATE)));
        this->startWait();
      }
      this->m_task();
    } else {
      if (boost::asio::error::operation_aborted == ec) {
        // FIXME
        std::cerr << "Operation aborted" << std::endl;
      } else {
        // FIXME
        std::cerr << "Other error" << std::endl;
      }
    }
  }

  void start() {
    this->m_timer.expires_from_now(boost::posix_time::milliseconds(this->m_offsetInterval));
    this->startWait();
  }

  void cancel() { this->m_timer.cancel(); }

private:
  void startWait() {
    this->m_timer.async_wait([this](const boost::system::error_code &ec) { this->execute(ec); });
  }

  std::function<void(void)> m_task;
  int m_offsetInterval;
  bool m_periodic;
  int m_interval;
  boost::asio::deadline_timer m_timer;
};

static void timeStep() {
  auto simTimeMillis = Timer::getInstance().simMillis();
  double simTimeInSeconds = static_cast<double>(simTimeMillis) / 1000;

  std::string simTimeStr = std::to_string(simTimeInSeconds);
  simTimeStr = simTimeStr.substr(0, simTimeStr.find('.') + 3); // Keep 2 decimal places

  nlohmann::json message;
  message["simTime"] = simTimeStr;
  message["missionTime"] = ""; // TODO: implement
  message["epochTime"] = "";   // TODO: implement
  message["zuluTime"] = "";    // TODO: implement

  Publisher::getInstance().queueMessage("TIME", message);
}

class BoostScheduler {
public:
  static BoostScheduler &getInstance() {
    static BoostScheduler instance;
    return instance;
  }

  void add_event(int offsetInterval, bool periodic, int interval, std::function<void(void)> &&fn) {
    this->m_events.push_back(std::make_shared<BoostEvent>(this->m_ioService, offsetInterval, periodic, interval, fn));
  }

  void start() {
    if (m_lastStopTicks != 0) {
      Timer::getInstance().updateInitialTicks(m_lastStopTicks);
    }

    m_isRunning = true;

    Logger::info("Simulation started");

    for (auto &event : m_events) {
      event->start();
    }
  }

  void stop() {
    m_isRunning = false;

    Logger::info("Simulation stopped");

    for (auto &event : m_events) {
      event->cancel();
    }

    m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }

  bool getIsRunning() const { return m_isRunning; }

private:
  BoostScheduler() : m_work(m_ioService), m_workingThread([this]() { this->m_ioService.run(); }) {
    add_event(0, true, 100, [&]() { timeStep(); });
  }

  ~BoostScheduler() {
    this->m_ioService.stop();
    this->m_workingThread.join();
  }

  boost::asio::io_service m_ioService;
  boost::asio::io_service::work m_work;
  std::thread m_workingThread;
  std::vector<std::shared_ptr<BoostEvent>> m_events;
  bool m_isRunning{};
  long long m_lastStopTicks{};
};
