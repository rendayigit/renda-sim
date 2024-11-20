#pragma once

#include "services/eventManager/eventManager.hpp"

class Scheduler {
public:
  static Scheduler &getInstance() {
    static Scheduler instance;
    return instance;
  }

  void start() {
    
  }

  void progressSimulation(unsigned int ticks) {
    // Set new simulation time
    m_simTick += ticks;

    // Iterate through all events in the simulation
    for (auto &event : EventManager::getInstance().getEventQueue()) {
      if (event->isActive()) {
        double cycle = event->getCycleTicks();
        if (cycle > 0) { // If the event is periodic
          double tickProgress = 0.0;
          while (tickProgress < ticks) { // Process the event enough cycles for the given amount of ticks
            event->process();            // Process the event
            tickProgress += event->getCycleTicks();
          }
        } else {                                   // If the event is single shot
          if (event->getNextTick() <= m_simTick) { // Process the event if it is due
            event->process();                      // Process the event
          }
        }
      }
    }
  }

private:
  Scheduler() = default;
  unsigned int m_simTick = 0;
};