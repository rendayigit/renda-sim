#pragma once

#include "messaging/messaging.hpp"

class Engine {
public:
  Engine() = default;

  void init() {}

  void run() { // Instantiate messaging
    Messaging::getInstance();
  }
};