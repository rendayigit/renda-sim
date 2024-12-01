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
      : m_stepTimeMicros(Json(CONFIG_PATH).getNode("SCHEDULER_STEP_TIME_MICROS").getValue<double>()),
        m_rate(Json(CONFIG_PATH).getNode("SCHEDULER_DEFAULT_RATE").getValue<double>()),
        m_eventManagerInstance(eventManager), m_eventQueueInstance(m_eventManagerInstance->getEventQueue()) {}

  ~Scheduler() { stop(); }

  void start();
  void stop();
  void reset();

  void progressTime(long millis);

  bool isRunning() const { return m_isRunning; }

private:
  void step(long currentMillis) const;

  double m_stepTimeMicros;
  double m_rate;

  std::thread m_schedulerThread;
  bool m_isRunning = false;

  long long m_lastStopTicks{};
  long m_progressTimeLastMillis{};

  EventManager *m_eventManagerInstance;
  std::vector<Event *> *m_eventQueueInstance;
};