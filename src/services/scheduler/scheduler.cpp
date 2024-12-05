#include <chrono>
#include <iostream>
#include <string>

#include "services/scheduler/scheduler.hpp"
#include "services/timer/timer.hpp"

#include "services/messaging.hpp"

constexpr int MICROS_TO_MILLIS = 1000;
constexpr int MILLIS_TO_SECS = 1000;

void Scheduler::start() {
  if (m_lastStopTicks != 0) {
    Timer::getInstance().updateInitialTicks(m_lastStopTicks);
  }

  m_isRunning = true;
  std::cout << "***** Simulation Start *****" << std::endl;

  m_schedulerThread = std::thread([&] {
    while (m_isRunning) {
      std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long>(m_stepTimeMicros * MICROS_TO_MILLIS)));
      step(static_cast<long>(static_cast<double>(Timer::getInstance().simMillis()) * m_rate));
    }
  });
}

void Scheduler::stop() {
  m_isRunning = false;
  std::cout << "***** Simulation Stop *****" << std::endl;

  if (m_schedulerThread.joinable()) {
    m_schedulerThread.join();
  }

  m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

void Scheduler::reset() {
  Timer::getInstance().reset();
  // TODO(renda): Reset all events and models
}

void Scheduler::progressTime(long millis) {
  m_progressTimeLastMillis += millis;
  step(m_progressTimeLastMillis);
}

void Scheduler::step(long currentMillis) const {
  double timeInSeconds = static_cast<double>(currentMillis) / MILLIS_TO_SECS;
  std::string timeStr = std::to_string(timeInSeconds);
  timeStr = timeStr.substr(0, timeStr.find('.') + 3); // Keep 2 decimal places
  // TODO(renda): Transmit time
  Messaging::getInstance().queueMessage("SIM_TIME", timeStr);

  while (true) {
    // Skip if no events in queue
    if (m_eventQueueInstance->empty()) {
      return;
    }

    // Get the nearest event
    Event *event = m_eventQueueInstance->at(0);

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
