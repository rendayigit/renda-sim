#pragma once

#include "dataInterface.hpp"
#include "model/modelVariable.hpp"
#include "modelVariable.hpp"
#include "simpleEvent.hpp"

class Payload : public Model {
public:
  Payload();

  void init();
  void step();

private:
  SimpleEvent m_event;

  // CSU
  ModelVariable<double> m_csuPower;
  ModelVariable<double> m_dcu1Power;
  ModelVariable<double> m_dcu2Power;
  ModelVariable<double> m_afsCuPower;

  // HCU
  ModelVariable<DataStruct> m_tmd1A;
  ModelVariable<DataStruct> m_tmd1B;
  ModelVariable<DataStruct> m_spp1A;
  ModelVariable<DataStruct> m_spp1B;
  ModelVariable<DataStruct> m_upp1A;
  ModelVariable<DataStruct> m_upp1B;
};