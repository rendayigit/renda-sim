#pragma once

#include "common/modelVariable.hpp"
#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/logger/logger.hpp"
#include <string>

class SampleModel : Model {
public:
  SampleModel();
  void step(int stepTime);

private:
  Logger m_logger;

  SimpleEvent *m_eventSlow;
  SimpleEvent *m_eventFast;
  SimpleEvent *m_eventFaster;
  SimpleEvent *m_eventFastest;

  ModelVariable<double> m_doubleValue;
  ModelVariable<int> m_integerValue;
  ModelVariable<bool> m_booleanValue;
  ModelVariable<std::string> m_stringValue;
};