#pragma once

#include <string>
#include <thread>
#include <vector>

#include "services/eventManager/eventManager.hpp"
#include "services/fileOperations.hpp"
#include "services/json/json.hpp"

const std::string CONFIG_PATH = FileOperations::getInstance().getExecutableDirectory() + "/../config.json";

class Scheduler {
public:
  explicit Scheduler(EventManager *eventManager)
      : m_stepTime(Json(CONFIG_PATH).getNode("SCHEDULER_STEP_TIME").getValue<double>()),
        m_rate(Json(CONFIG_PATH).getNode("SCHEDULER_DEFAULT_RATE").getValue<double>()),
        m_eventManagerInstance(eventManager), m_eventQueueInstance(m_eventManagerInstance->getEventQueue()) {}

  void start();

  void progressTime(long millis);

private:
  void step(long currentMillis) const;

  double m_stepTime;
  double m_rate;

  std::thread m_schedulerThread;
  EventManager *m_eventManagerInstance;
  std::vector<Event *> *m_eventQueueInstance;
  long m_progressTimeLastMillis{};
};