#pragma once

#include "services/eventManager/eventManager.hpp"

class Scheduler {
public:
  void progressSimulation(double seconds) {
    // Set new simulation time
    simTime += seconds;

    // Iterate through all events in the simulation
    for (auto &event : EventManager::getInstance().getEventQueue()) {
      if (event->isActive()) {
        double cycle = event->getCycleMs();
        // If the event is periodic
        if (cycle > 0) {
          // Process the event enough cycles for the given amount of time
          double timeProgress = 0.0;
          while (timeProgress < seconds) {
            // Process the event
            event->process();

            timeProgress += event->getCycleMs();
          }
          // If the event is single shotl
        } else {
          // Process the event if its schedule is due
          if ((event->getNextTick() / 1000000) <= simTime) {
            // Process the event
            event->process();
          }
        }
      }
    }
  }

private:
  double simTime;
};