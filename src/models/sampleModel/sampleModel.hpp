#pragma once

#include <string>

#include "common/modelVariable.hpp"
#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "spdlog/sinks/daily_file_sink.h"

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

  std::shared_ptr<spdlog::logger> m_logger; // TODO(renda): replace old logger with this one
};