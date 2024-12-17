#pragma once

#include <iostream>

#include "messaging/messaging.hpp"
#include "scheduler/scheduler.hpp"

class Engine {
public:
  static void run() { // Instantiate messaging
    Messaging::getInstance().start();

    std::cout << "\nPress enter to stop the simulation\n\n";
    char input = 0;
    while (input != '\n') {
      std::cin.get(input);
    }

    Scheduler::getInstance().stop();
    Messaging::getInstance().stop();
  }
};