#include "scheduler/scheduler.hpp"

#include <chrono>
#include <fstream>
#include <string>

#include "common.hpp"
#include "logger/logger.hpp"
#include "messaging/publisher.hpp"
#include "timer/timer.hpp"

constexpr int MICROS_TO_MILLIS = 1000;
constexpr int MILLIS_TO_SECS = 1000;
constexpr int LOGGER_RATE_MULTIPLIER = 100;

Scheduler::Scheduler()
    : m_work(m_ioService), m_workingThread([&] { m_ioService.run(); }), m_schedulerTimer(m_ioService),
      m_durationTimer(m_ioService) {
  nlohmann::json config;

  std::ifstream configFile(CONFIG_PATH);
  if (not configFile.is_open()) {
    Logger::error("Could not open the config file: " + CONFIG_PATH);
  } else {
    try {
      configFile >> config;

      if (config.contains("SCHEDULER_STEP_TIME_MILLIS") and config["SCHEDULER_STEP_TIME_MILLIS"].is_number_integer()) {
        m_stepTimeMillis = config["SCHEDULER_STEP_TIME_MILLIS"].get<long>();
      } else {
        Logger::error("Key 'SCHEDULER_STEP_TIME_MILLIS' not found or is not a float.");
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
  m_ioService.stop();

  if (m_workingThread.joinable()) {
    m_workingThread.join();
  }
}

void Scheduler::execute(boost::system::error_code const &errorCode) {
  if (not errorCode) {
    long nextScheduleMillis = m_stepTimeMillis / m_rate;
    m_schedulerTimer.expires_at(m_schedulerTimer.expires_at() + boost::posix_time::milliseconds(nextScheduleMillis));
    m_schedulerTimer.async_wait([this](const boost::system::error_code &newErrorCode) { execute(newErrorCode); });
    step();
  } else {
    if (errorCode != boost::asio::error::operation_aborted) {
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

  m_schedulerTimer.expires_from_now(boost::posix_time::milliseconds(0));
  m_schedulerTimer.async_wait([this](const boost::system::error_code &errorCode) { execute(errorCode); });
}

void Scheduler::stop() {
  Logger::info("Simulation stopped");

  m_isRunning = false;

  m_schedulerTimer.cancel();

  m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Scheduler::setRate(double rate) { m_rate = rate; }

void Scheduler::runFor(long millis) {
  start();
  stopIn(millis);
}

void Scheduler::runUntil(const nlohmann::json &time) {
  start();
  stopAt(time);
}

void Scheduler::stopAt(const nlohmann::json &time) {
  auto hour = time["hours"].get<int>();
  auto minute = time["minutes"].get<int>();
  auto second = time["seconds"].get<int>();
  auto millisecond = time["milliseconds"].get<int>();

  auto now = boost::posix_time::microsec_clock::local_time();

  boost::posix_time::ptime expirationTime(
      now.date(), boost::posix_time::hours(hour) + boost::posix_time::minutes(minute) +
                      boost::posix_time::seconds(second) + boost::posix_time::milliseconds(millisecond));

  // If the expiration time has already passed today, schedule it for tomorrow
  if (expirationTime < now) {
    expirationTime += boost::posix_time::hours(24);
  }

  // Calculate the duration to wait
  boost::posix_time::time_duration duration = expirationTime - now;

  m_durationTimer.expires_from_now(duration);

  m_durationTimer.async_wait([&](const boost::system::error_code &errorCode) {
    if (not errorCode) {
      stop();
    } else {
      Logger::warn("Unable to stop simulation at " + std::to_string(hour) + ":" + std::to_string(minute) + ":" +
                   std::to_string(second) + ":" + std::to_string(millisecond));
    }
  });
}

void Scheduler::stopIn(long millis) {
  m_durationTimer.expires_from_now(boost::posix_time::milliseconds(millis));
  m_durationTimer.async_wait([&](const boost::system::error_code &errorCode) {
    if (not errorCode) {
      stop();
    } else {
      Logger::warn("Unable to stop simulation in " + std::to_string(millis) + " milliseconds");
    }
  });
}

void Scheduler::step() {
  m_currentMillis += m_stepTimeMillis;
  transmitTime(m_currentMillis); // This step is resource intensive

  // Skip if no events in queue
  if (m_eventQueueInstance->empty()) {
    return;
  }

  for (auto &event : *m_eventQueueInstance) {
    // Skip if event is not active
    if (not event->isActive()) {
      continue;
    }

    // Skip if event is not due
    if (event->getNextMillis() > m_currentMillis) {
      continue;
    }

    // Process the event
    event->process();

    // If the event is single shot remove the event from queue
    if (event->getCycleMillis() < 0) {
      m_eventManagerInstance->removeEvent(event);
      continue;
    }

    // Update event if event is cyclic and repeat loop
    event->setNextMillis(event->getNextMillis() + event->getCycleMillis());
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
