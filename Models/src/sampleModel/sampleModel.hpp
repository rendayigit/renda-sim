#pragma once

#include <string>
#include <vector>

#include "modelVariable.hpp"
#include "simpleEvent.hpp"

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

  std::vector<ModelVariable<int> *> m_arrayValue; // TODO(renda): improve array support

  ModelVariable<std::vector<int>> *m_modelVarVector;

  ModelVariable<unsigned int> m_uintValue;
};