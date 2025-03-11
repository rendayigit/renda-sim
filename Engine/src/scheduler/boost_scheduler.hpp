#pragma once

#include "logger/logger.hpp"
#include "messaging/publisher.hpp"
#include "timer/timer.hpp"
#include <iostream>

#include <thread>
#include <vector>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>

constexpr double SIM_RATE = 1.0;

class BoostEvent : public boost::noncopyable {
public:
  using entrypoint = std::function<void(void)>;

  BoostEvent(boost::asio::io_service &io_service, int offset_interval, bool periodic, int interval, entrypoint task)
      : task(task), offset_interval(offset_interval), periodic(periodic), interval(interval), timer(io_service) {
    // Schedule start to be ran by the io_service
    io_service.post(boost::bind(&BoostEvent::start, this));
  }

  ~BoostEvent() { std::cout << "Event destroyed" << std::endl; }

  void execute(boost::system::error_code const &ec) {
    if (!ec) {
      if (this->periodic) {
        // timer.expires_at(timer.expires_at() + boost::posix_time::milliseconds(this->interval));
        timer.expires_at(timer.expires_at() +
                         boost::posix_time::milliseconds(static_cast<int>(this->interval / SIM_RATE)));
        this->start_wait();
      }
      this->task();
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
    this->timer.expires_from_now(boost::posix_time::milliseconds(this->offset_interval));
    this->start_wait();
  }

  void cancel() { this->timer.cancel(); }

private:
  void start_wait() {
    this->timer.async_wait(boost::bind(&BoostEvent::execute, this, boost::asio::placeholders::error));
  }

  entrypoint task;
  int offset_interval;
  bool periodic;
  int interval;
  boost::asio::deadline_timer timer;
};

static void time_step() {
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

  void add_event(int offset_interval, bool periodic, int interval, BoostEvent::entrypoint &&fn) {
    this->events.push_back(std::make_shared<BoostEvent>(this->io_service, offset_interval, periodic, interval, fn));
  }

  void start() {
    if (m_lastStopTicks != 0) {
      Timer::getInstance().updateInitialTicks(m_lastStopTicks);
    }

    isRunning = true;

    Logger::info("Simulation started");

    for (auto &event : events) {
      event->start();
    }
  }

  void stop() {
    isRunning = false;

    Logger::info("Simulation stopped");

    for (auto &event : events) {
      event->cancel();
    }

    m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }

  bool getIsRunning() const { return isRunning; }

private:
  BoostScheduler() : work(io_service), working_thread([this]() { this->io_service.run(); }), isRunning(true) {
    add_event(0, true, 100, [&]() { time_step(); });
  }

  ~BoostScheduler() {
    this->io_service.stop();
    this->working_thread.join();
  }

  boost::asio::io_service io_service;
  boost::asio::io_service::work work;
  std::thread working_thread;
  std::vector<std::shared_ptr<BoostEvent>> events;
  bool isRunning;
  long long m_lastStopTicks{};
};