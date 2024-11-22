#pragma once

#include <chrono>
// #include <cstddef>
#include <thread>
#include <vector>

#include "services/eventManager/eventManager.hpp"

class Scheduler {
public:
  explicit Scheduler(EventManager *eventManager)
      : m_appStartTime(std::chrono::high_resolution_clock::now()), m_eventManagerInstance(eventManager),
        m_eventQueueInstance(m_eventManagerInstance->getEventQueue()) {}

  void start();

  void progressTime(long millis);

private:
  void step(long currentMillis) const;

  std::chrono::system_clock::time_point m_appStartTime;
  std::thread m_schedulerThread;
  EventManager *m_eventManagerInstance;
  std::vector<Event *> *m_eventQueueInstance;
  long m_progressTimeLastMillis{};
};