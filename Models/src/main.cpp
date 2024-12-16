#include <iostream>

#include "engine.hpp"

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  SampleModel sampleModel;
  PowerSubsystem powerSubsystem;

  Engine engine;
  engine.run();

  std::cout << "\nPress enter to stop the simulation\n\n";
  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
