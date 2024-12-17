#pragma once

#include <iostream>

#include "messaging/messaging.hpp"

class Engine {
public:
  Engine() = default;

  void init() {}

  void run() { // Instantiate messaging
    Messaging::getInstance();

    std::cout << "\nPress enter to stop the simulation\n\n";
    char input = 0;
    while (input != '\n') {
      std::cin.get(input);
    }
  }
};