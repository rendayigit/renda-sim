#include <iostream>

#include "models/pcs/pcs.hpp"
#include "models/sampleModel/sampleModel.hpp"

#include "engine/messaging/messaging.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  SampleModel sm;
  PowerSubsystem powerSubsystem;

  // Instantiate messaging
  Messaging::getInstance();

  std::cout << "\nPress enter to stop the simulation\n\n";
  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
