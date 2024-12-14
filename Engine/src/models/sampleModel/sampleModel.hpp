#pragma once

#include <string>

#include "engine/eventManager/simpleEvent.hpp"
#include "engine/model/modelVariable.hpp"

class SampleModel : public Model {
public:
  SampleModel();
  void step(int stepTime);

private:
  SimpleEvent *m_eventSlow;
  SimpleEvent *m_eventFast;
  SimpleEvent *m_eventFaster;
  SimpleEvent *m_eventFastest;

  ModelVariable<double> m_doubleValue;
  ModelVariable<int> m_integerValue;
  ModelVariable<bool> m_booleanValue;
  ModelVariable<std::string> m_stringValue;
};