#include "services/scheduler/scheduler.hpp"

void Scheduler::start() {
  m_schedulerThread = std::thread([&] {
    while (true) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      auto now = std::chrono::high_resolution_clock::now();
      auto currentMillis = std::chrono::duration<double, std::milli>(now - m_appStartTime).count();
      step(currentMillis);
    }
  });
}

void Scheduler::progressTime(long millis) {
  m_progressTimeLastMillis += millis;
  step(m_progressTimeLastMillis);
}

void Scheduler::step(long currentMillis) const {
  while (true) {
    // Skip if event no events in queue
    if (m_eventQueueInstance->empty()) {
      return;
    }

    // Get the event at the top of the event queue
    Event *event = m_eventQueueInstance->at(0);

    // Skip if event is null or is not active
    if (not event->isActive()) {
      return;
    }

    // Skip if nearest event is not due
    if (event->getNextMillis() > currentMillis) {
      return;
    }

    // Process the event
    event->process();

    // Pop nearest event
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

