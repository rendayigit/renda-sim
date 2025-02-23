#pragma once

#include <iostream>

#include "messaging/commanding.hpp"
#include "scheduler/scheduler.hpp"

class Engine {
public:
  static void run() {
    Commanding::getInstance().start(); // Instantiate messaging

    std::cout << "\nPress enter to stop the simulation\n\n";
    char input = 0;
    while (input != '\n') {
      std::cin.get(input);
    }

    Scheduler::getInstance().stop();
    Commanding::getInstance().stop();
  }

private:
  Engine() = default;
};