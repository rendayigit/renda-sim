#pragma once

#include <chrono>
#include <cstddef>
#include <thread>
#include <vector>

#include "services/eventManager/eventManager.hpp"

class Scheduler {
public:
  static Scheduler &getInstance() {
    static Scheduler instance;
    return instance;
  }

  void start() {
    m_schedulerThread = std::thread([&] {
      while (true) {
        auto now = std::chrono::steady_clock::now();
        auto currentMillis = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_appStartTime).count();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        step(currentMillis);
      }
    });
  }

  void progressTime(long millis) const {
    static long currentMillis = 0.0;
    currentMillis += millis;

    for (long i = 0; i < millis; i++) {
      step(i);
    }
  }

private:
  Scheduler()
      : m_appStartTime(std::chrono::steady_clock::now()), m_eventManagerInstance(&EventManager::getInstance()),
        m_eventQueueInstance(m_eventManagerInstance->getEventQueue()) {}

  void step(long currentMillis) const {
    while (true) {
      // Get the event at the top of the event queue
      Event *event = m_eventQueueInstance->at(0);

      // Skip if event is null or is not active
      if (event == nullptr or not event->isActive()) {
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

  std::chrono::steady_clock::time_point m_appStartTime;
  std::thread m_schedulerThread;
  EventManager *m_eventManagerInstance;
  std::vector<Event *> *m_eventQueueInstance;
};