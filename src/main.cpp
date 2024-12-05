#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"

#include "services/messaging.hpp" // TODO(renda): Move somewhere else

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "Press enter to stop the simulation\n\n";

  Messaging m; // TODO(renda): Move somewhere else

  // Instantiate models
  SampleModel sm;
  PowerSubsystem powerSubsystem;

  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
