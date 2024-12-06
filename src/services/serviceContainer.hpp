#pragma once

#include "services/eventManager/eventManager.hpp"
// #include "services/messaging.hpp"
#include "services/logger/logger.hpp"
#include "services/scheduler/scheduler.hpp"
#include "services/timer/timer.hpp"

class ServiceContainer {
public:
  static ServiceContainer &getInstance() {
    static ServiceContainer instance;
    return instance;
  }

  Scheduler *scheduler() const { return m_scheduler; }
  EventManager *eventManager() const { return m_eventManager; }
  static Timer timer() { return Timer::getInstance(); }
  Logger *logger() const { return m_logger; }

private:
  ServiceContainer()
      : m_eventManager(new EventManager), m_scheduler(new Scheduler(m_eventManager)) /*, m_messaging(new Messaging)*/,
        m_logger(new Logger) {}

  EventManager *m_eventManager;
  Scheduler *m_scheduler;
  Logger *m_logger;
  // Messaging *m_messaging;
};