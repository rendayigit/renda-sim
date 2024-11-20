#pragma once

#include "services/modelEvent.hpp"

class SampleModel {
public:
  SampleModel();
  static void step();

private:
  ModelEvent *m_event;
};