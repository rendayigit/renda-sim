#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/serviceContainer.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "Simulation Start" << std::endl;

  ServiceContainer::getInstance().scheduler()->start();

  SampleModel sm;

  PowerSubsystem powerSubsystem;

  std::cin.get();

  return 0;
}
