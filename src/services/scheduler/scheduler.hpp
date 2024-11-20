#pragma once

#include <chrono>
#include <thread>

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
        progressSimulation(-1);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
  }

  void progressSimulation(long millis = 0) const {
    static long currentMillis = 0.0;

    if (millis <= 0) {
      auto now = std::chrono::steady_clock::now();
      currentMillis = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_appStartTime).count();
    } else {
      currentMillis += millis;
    }

    // Iterate through all events in the simulation
    for (auto &event : EventManager::getInstance().getEventQueue()) {
      if (not event->isActive()) { // Skip event if event not active
        continue;
      }

      // Enter loop if event is due
      while (event->getNextMillis() <= currentMillis) {
        // Process the event
        event->process();

        // If the event is single shot exit loop
        if (event->getCycleMillis() <= 0) {
          break;
        }

        // Reschedule event if event is cyclic and repeat loop
        event->setNextMillis(event->getNextMillis() + event->getCycleMillis());
      }
    }
  }

private:
  Scheduler() = default;

  std::chrono::steady_clock::time_point m_appStartTime = std::chrono::steady_clock::now();
  std::thread m_schedulerThread;
};