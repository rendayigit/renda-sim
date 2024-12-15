#include <iostream>

#include "engine/messaging/messaging.hpp"
#include "root.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  Root root;
  root.init();

  // Run the model
  root.run();

  // Instantiate messaging
  Messaging::getInstance();

  std::cout << "\nPress enter to stop the simulation\n\n";
  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
