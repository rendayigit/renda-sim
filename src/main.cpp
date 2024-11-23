#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/serviceContainer.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "\n***** Simulation Start *****\n\n";

  ServiceContainer::getInstance().scheduler()->start();

  SampleModel sm;

  PowerSubsystem powerSubsystem;

  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  ServiceContainer::getInstance().scheduler()->stop();

  std::cout << "\n****** Simulation End ******\n\n";

  return 0;
}
