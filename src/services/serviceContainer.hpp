#pragma once

#include "services/eventManager/eventManager.hpp"
#include "services/scheduler/scheduler.hpp"

class ServiceContainer {
public:
  static ServiceContainer &getInstance() {
    static ServiceContainer instance;
    return instance;
  }

  Scheduler *scheduler() const { return m_scheduler; }
  EventManager *eventManager() const { return m_eventManager; }

private:
  ServiceContainer() : m_eventManager(new EventManager), m_scheduler(new Scheduler(m_eventManager)) {}

  EventManager *m_eventManager;
  Scheduler *m_scheduler;
};