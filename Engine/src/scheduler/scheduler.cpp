#include "scheduler/scheduler.hpp"

#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

#include "common.hpp"
#include "logger/logger.hpp"
#include "messaging/publisher.hpp"
#include "timer/timer.hpp"

constexpr int MICROS_TO_MILLIS = 1000;
constexpr int MILLIS_TO_SECS = 1000;
constexpr int LOGGER_RATE_MULTIPLIER = 100;

Scheduler::Scheduler() : m_work(m_ioService), m_workingThread([&] { this->m_ioService.run(); }), m_timer(m_ioService) {
  nlohmann::json config;

  std::ifstream configFile(CONFIG_PATH);
  if (not configFile.is_open()) {
    Logger::error("Could not open the config file: " + CONFIG_PATH);
  } else {
    try {
      configFile >> config;

      if (config.contains("SCHEDULER_STEP_TIME_MICROS") and config["SCHEDULER_STEP_TIME_MICROS"].is_number_float()) {
        m_stepTimeMicros = config["SCHEDULER_STEP_TIME_MICROS"].get<double>();
      } else {
        Logger::error("Key 'SCHEDULER_STEP_TIME_MICROS' not found or is not a float.");
      }

      if (config.contains("SCHEDULER_DEFAULT_RATE") and config["SCHEDULER_DEFAULT_RATE"].is_number_float()) {
        m_rate = config["SCHEDULER_DEFAULT_RATE"].get<double>();
      } else {
        Logger::error("Key 'SCHEDULER_DEFAULT_RATE' not found or is not a float.");
      }

    } catch (const nlohmann::json::parse_error &e) {
      Logger::critical("JSON parse error: " + std::string(e.what()));
    }
  }
}

Scheduler::~Scheduler() {
  stop();
  m_lastStopTicks = {};
  m_progressTimeLastMillis = {};

  this->m_ioService.stop();
  this->m_workingThread.join();
}

void Scheduler::execute(boost::system::error_code const &errorCode) {
  if (not errorCode) {
    m_timer.expires_at(m_timer.expires_at() + boost::posix_time::milliseconds(100));
    this->m_timer.async_wait([this](const boost::system::error_code &ec) { this->execute(ec); });
    step(static_cast<long>(static_cast<double>(Timer::getInstance().simMillis()) * m_rate));
  } else {
    if (boost::asio::error::operation_aborted == errorCode) {
      // TODO handle
      Logger::warn("Scheduler aborted");
    } else {
      // TODO handle
      Logger::warn("Scheduler error");
    }
  }
}

void Scheduler::start() {
  if (m_lastStopTicks != 0) {
    Timer::getInstance().updateInitialTicks(m_lastStopTicks);
  }

  m_isRunning = true;
  Logger::info("Simulation started");

  setRate(m_rate);

  this->m_timer.expires_from_now(boost::posix_time::milliseconds(0));
  this->m_timer.async_wait([this](const boost::system::error_code &ec) { this->execute(ec); });
}

void Scheduler::stop() {
  m_isRunning = false;

  Logger::info("Simulation stopped");

  this->m_timer.cancel();

  m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Scheduler::reset() {
  Timer::getInstance().reset();
  // TODO(renda): Reset all events and models
}

void Scheduler::setRate(double rate) { m_rate = rate; }

void Scheduler::progressTime(long millis) {
  m_progressTimeLastMillis += millis;
  step(m_progressTimeLastMillis);
}

void Scheduler::step(long currentMillis) {
  transmitTime(currentMillis);

  while (true) {
    // Skip if no events in queue
    if (m_eventQueueInstance->empty()) {
      return;
    }

    // Get the nearest event
    Event *event = m_eventQueueInstance->front();

    // Skip if event is not active
    if (not event->isActive()) {
      return;
    }

    // Skip if event is not due
    if (event->getNextMillis() > currentMillis) {
      return;
    }

    // Process the event
    event->process();

    // Pop event
    m_eventManagerInstance->removeEvent(event);

    // If the event is single shot do not reschedule event
    if (event->getCycleMillis() < 0) {
      return;
    }

    // Reschedule event if event is cyclic and repeat loop
    event->setNextMillis(event->getNextMillis() + event->getCycleMillis());
    m_eventManagerInstance->addEvent(event);
  }
}

void Scheduler::transmitTime(long simTimeMillis) {
  double simTimeInSeconds = static_cast<double>(simTimeMillis) / MILLIS_TO_SECS;

  std::string simTimeStr = std::to_string(simTimeInSeconds);
  simTimeStr = simTimeStr.substr(0, simTimeStr.find('.') + 3); // Keep 2 decimal places

  nlohmann::json message;
  message["simTime"] = simTimeStr;
  message["missionTime"] = ""; // TODO: implement
  message["epochTime"] = "";   // TODO: implement
  message["zuluTime"] = "";    // TODO: implement

  Publisher::getInstance().queueMessage("TIME", message);
}
