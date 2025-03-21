#include "scheduler/scheduler.hpp"

#include <cstddef>
#include <string>

#include "logger/logger.hpp"
#include "messaging/publisher.hpp"

constexpr int MICROS_TO_MILLIS = 1000;
constexpr int MILLIS_TO_SECS = 1000;
constexpr int LOGGER_RATE_MULTIPLIER = 100;
constexpr long STEP_TIME_MILLIS = 10;

Scheduler::Scheduler()
    : m_work(m_ioService), m_workingThread([&] { m_ioService.run(); }), m_schedulerTimer(m_ioService),
      m_durationTimer(m_ioService) {}

Scheduler::~Scheduler() {
  reset();

  if (not m_ioService.stopped()) {
    m_ioService.stop();
  }

  if (m_workingThread.joinable()) {
    m_workingThread.join();
  }
}

void Scheduler::execute(boost::system::error_code const &errorCode) {
  if (not errorCode) {
    if (m_rate > STEP_TIME_MILLIS) {
      m_rate = STEP_TIME_MILLIS;
      Logger::warn("Rate cannot be more than " + std::to_string(STEP_TIME_MILLIS) + ". Rate is now set to " +
                   std::to_string(STEP_TIME_MILLIS));
    }

    long nextScheduleMillis = STEP_TIME_MILLIS / m_rate;

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
  m_isRunning = true;
  Logger::info("Simulation started");

  m_schedulerTimer.expires_from_now(boost::posix_time::milliseconds(0));
  execute(boost::system::error_code());

  nlohmann::json status;
  status["schedulerIsRunning"] = Scheduler::getInstance().isRunning();
  Publisher::getInstance().queueMessage("STATUS", status);
}

void Scheduler::stop() {
  Logger::info("Simulation stopped");

  m_isRunning = false;

  m_schedulerTimer.cancel();

  nlohmann::json status;
  status["schedulerIsRunning"] = Scheduler::getInstance().isRunning();
  Publisher::getInstance().queueMessage("STATUS", status);
}

void Scheduler::setRate(double rate) { m_rate = rate; }

void Scheduler::progressSim(long millis) {
  for (int i = 0; i < millis / STEP_TIME_MILLIS; i++) {
    step();
  }
}

void Scheduler::reset() {
  if (m_isRunning) {
    stop();
  }

  m_currentMillis = {};
}

void Scheduler::step() {
  std::lock_guard<std::mutex> lock(m_mutex);

  m_currentMillis += STEP_TIME_MILLIS;

  transmitTime(m_currentMillis);

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
