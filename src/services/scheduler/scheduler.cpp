#include <chrono>
#include <iostream>

#include "services/scheduler/scheduler.hpp"
#include "services/timer/timer.hpp"

void Scheduler::start() {
  // TODO(renda): correctly update time here
  // Timer::getInstance().reset();

  m_isRunning = true;

  std::cout << "\n***** Simulation Start *****\n";

  m_schedulerThread = std::thread([&] {
    while (m_isRunning) {
      std::this_thread::sleep_for(std::chrono::microseconds(static_cast<long>(m_stepTime * 1000)));
      step(Timer::getInstance().currentMillis() * m_rate);
    }
  });
}

void Scheduler::stop() {
  m_isRunning = false;
  std::cout << "\n****** Simulation End ******\n\n";

  if (m_schedulerThread.joinable()) {
    m_schedulerThread.join();
  }
}

void Scheduler::progressTime(long millis) {
  m_progressTimeLastMillis += millis;
  step(m_progressTimeLastMillis);
}

void Scheduler::step(long currentMillis) const {
  // TODO(renda): Added to debug scheduler stop function
  std::cout << "TIME: " << currentMillis << " ms" << std::endl;

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
