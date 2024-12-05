#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/serviceContainer.hpp"
#include "services/messaging.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  ServiceContainer::getInstance().scheduler()->start();
  std::cout << "Press enter to stop the simulation\n\n";

  Messaging m;

  SampleModel sm;

  PowerSubsystem powerSubsystem;

  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  ServiceContainer::getInstance().scheduler()->stop();

  return 0;
}
