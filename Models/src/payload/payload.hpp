#pragma once

#include "modelVariable.hpp"
#include "simpleEvent.hpp"

class Payload : public Model {
public:
  Payload();

  void init();
  void step();

private:
  SimpleEvent m_event;

  ModelVariable<double> m_value;
};