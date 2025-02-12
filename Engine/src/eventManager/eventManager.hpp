#pragma once

#include <vector>

class Event {
public:
  virtual ~Event() = default;

  /**
   * Sets the cycle time for the event based on the input time.
   *
   * @param cycleTime The amount of time between cycles or repetitions. Time unit is in milliseconds.
   *
   * @throws None
   */
  void setCycleMillis(long millis) { m_cycleMillis = millis; }

  /**
   * Returns the cycle time for the event if the event is cyclic.
   *
   * @return Cycle time, is the amount of time between cycles or repetitions. Time unit is in
   * milliseconds.
   *
   * @throws None
   */
  long getCycleMillis() const { return m_cycleMillis; }

  /**
   * Sets the tick at which the event will trigger.
   *
   * @param tick Ttick at which the event will trigger.
   *
   * @throws None
   */
  void setNextMillis(long millis) { m_nextMillis = millis; }

  long getNextMillis() const { return m_nextMillis; }

  /**
   * Activates the event. An event cannot trigger if not activated.
   *
   * @throws None
   */
  void activate() { m_isActive = true; }

  /**
   * Deactivates the event. An event cannot trigger if not activated.
   *
   * @throws None
   */
  void deactivate() { m_isActive = false; }

  /**
   * Returns if the event is active or not. An event cannot trigger if not activated.
   *
   * @return Boolean value to indicate if event is active or not.
   *
   * @throws None
   */
  bool isActive() const { return m_isActive; }

  virtual void process() = 0;

private:
  long m_cycleMillis = -1;
  long m_nextMillis{};
  bool m_isActive{};
};

class EventManager {
public:
  static EventManager &getInstance() {
    static EventManager instance;
    return instance;
  }

  void addEvent(Event *event);

  void removeEvent(Event *event);

  std::vector<Event *> *getEventQueue() const { return m_eventQueue; }

private:
  EventManager() = default;
  std::vector<Event *> *m_eventQueue = new std::vector<Event *>;
};