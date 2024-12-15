#pragma once

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"

class Root {
public:
  Root();
  void init();
  void run();

private:
  SampleModel *m_sampleModel;
  PowerSubsystem *m_powerSubsystem;
};