#ifndef MODELEVENT_HPP
#define MODELEVENT_HPP

#include <functional>
#include <utility>

#include "eventManager/eventManager.hpp"

#define SEC_TO_TICK(sec) sec * 1000000

class ModelEvent : public Event {
public:
  ModelEvent() {
    // EventManager::getInstance().addEvent(this);
  }

  // ~ModelEvent() override { EventManager::getInstance().removeEvent(this); }

  /**
   * Sets the event callback function for the event.
   *
   * @param eventFunction The function to be set as the event callback function.
   *
   * @throws None
   */
  void setEventFunction(std::function<void()> eventFunction) { m_eventFunction = std::move(eventFunction); }

  /**
   * Sets the trigger time for the event based on the input time. Trigger time is ignored if cycle
   * time is not 0.
   *
   * @param time The simulation time value to set as the trigger time. Time unit is in seconds.
   *
   * @throws None
   */
  void setTriggerTime(double time) { setNextTick(SEC_TO_TICK(time)); }

  /**
   * Sets the cycle time for the event based on the input time.
   *
   * @param cycleTime The amount of time between cycles or repetitions. Time unit is in seconds.
   *
   * @throws None
   */
  void setCycleTime(double cycleTime) { setCycleMs(cycleTime); }

  /**
   * Returns the cycle time for the event.
   *
   * @return Cycle time, is the amount of time between cycles or repetitions. Time unit is in
   * seconds.
   *
   * @throws None
   */
  double getCycleTime() { return getCycleMs(); }

  /**
   * Returns the cycle tick for the event.
   *
   * @return Cycle tick, is the amount of ticks between cycles or repetitions.
   *
   * @throws None
   */
  unsigned int getCycleTicks() { return Event::getCycleTicks(); }

  /**
   * Activates the event. An event cannot trigger if not activated.
   *
   * @throws None
   */
  void activate() { Event::activate(); }

  /**
   * Deactivates the event. An event cannot trigger if not activated.
   *
   * @throws None
   */
  void deactivate() { Event::deactivate(); }

  /**
   * Returns if the event is active or not. An event cannot trigger if not activated.
   *
   * @return Boolean value to indicate if event is active or not.
   *
   * @throws None
   */
  bool isActive() { return Event::isActive(); }

protected:
  /**
   * Called when the event is added to the event manager.
   *
   * @throws None
   */
  void add() override {}

  /**
   * Called when the event is removed from the event manager.
   *
   * @throws None
   */
  void remove() override {}

  void process() override { m_eventFunction(); }

  std::function<void()> m_eventFunction;
};

#endif // MODELEVENT_HPP