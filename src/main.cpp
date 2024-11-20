#include <iostream>

#include "sampleModel/sampleModel.hpp"
#include "services/scheduler/scheduler.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "Simulation Start" << std::endl;

  Scheduler::getInstance().start();

  SampleModel sm;

  return 0;
}
