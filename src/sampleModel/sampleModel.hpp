#pragma once

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"

class SampleModel {
public:
  SampleModel();
  static void step();

private:
  SimpleEvent *m_event;
};