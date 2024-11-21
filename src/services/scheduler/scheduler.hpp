#pragma once

#include <chrono>
#include <cstddef>
#include <thread>
#include <vector>

#include "services/eventManager/eventManager.hpp"

class Scheduler {
public:
  explicit Scheduler(EventManager *eventManager)
      : m_appStartTime(std::chrono::high_resolution_clock::now()), m_eventManagerInstance(eventManager),
        m_eventQueueInstance(m_eventManagerInstance->getEventQueue()) {}

  void start() {
    m_schedulerThread = std::thread([&] {
      while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        auto now = std::chrono::high_resolution_clock::now();
        auto currentMillis = std::chrono::duration<double, std::milli>(now - m_appStartTime).count();
        step(currentMillis);
      }
    });
  }

  void progressTime(long millis) {
    m_progressTimeLastMillis += millis;
    step(m_progressTimeLastMillis);
  }

private:
  void step(long currentMillis) const {
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

  std::chrono::system_clock::time_point m_appStartTime;
  std::thread m_schedulerThread;
  EventManager *m_eventManagerInstance;
  std::vector<Event *> *m_eventQueueInstance;
  long m_progressTimeLastMillis{};
};