#pragma once

#include <chrono>

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"

class SampleModel {
public:
  SampleModel();
  void step(int stepTime);

private:
  SimpleEvent *m_eventSlow;
  SimpleEvent *m_eventFast;
  SimpleEvent *m_eventFaster;
  SimpleEvent *m_eventFastest;

  std::chrono::steady_clock::time_point m_appStartTime = std::chrono::steady_clock::now();
};