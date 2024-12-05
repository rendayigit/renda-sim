#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"


#include "services/messaging.hpp" // TODO(renda): Move somewhere else


int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  SampleModel sm;
  PowerSubsystem powerSubsystem;

  Messaging::getInstance().queueMessage("SIM_TIME", "-"); // TODO(renda): Move somewhere else

  std::cout << "\nPress enter to stop the simulation\n\n";
  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
