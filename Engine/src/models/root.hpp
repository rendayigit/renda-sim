#pragma once

#include "models/pcs/pcs.hpp"
#include "models/sampleModel/sampleModel.hpp"

class Root {
public:
  Root();
  void init();
  void run();

private:
  SampleModel *m_sampleModel;
  PowerSubsystem *m_powerSubsystem;
};