#pragma once

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/logger/logger.hpp"

class SampleModel {
public:
  SampleModel();
  void step(int stepTime);

private:
  Logger m_logger;

  SimpleEvent *m_eventSlow;
  SimpleEvent *m_eventFast;
  SimpleEvent *m_eventFaster;
  SimpleEvent *m_eventFastest;
};