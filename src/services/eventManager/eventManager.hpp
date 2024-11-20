#pragma once

#include <algorithm>
#include <queue>
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
  void setCycleMs(double milliseconds) { m_cycle = milliseconds * 1000000000; }

  /**
   * Returns the cycle time for the event if the event is cyclic.
   *
   * @return Cycle time, is the amount of time between cycles or repetitions. Time unit is in
   * milliseconds.
   *
   * @throws None
   */
  double getCycleMs() const { return m_cycle / 1000000000; }

  void setCycleTicks(unsigned int ticks) { m_cycle = ticks; }

  /**
   * Returns the cycle tick for the event if the event is cyclic.
   *
   * @return Cycle tick, is the amount of ticks between cycles or repetitions.
   *
   * @throws None
   */
  unsigned int getCycleTicks() const { return m_cycle; }

  /**
   * Sets the tick at which the event will trigger.
   *
   * @param tick Ttick at which the event will trigger.
   *
   * @throws None
   */
  void setNextTick(unsigned int tick) { m_nextTick = tick; }

  unsigned int getNextTick() const { return m_nextTick; }

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

  /**
   * Called when the event is added to the event manager.
   *
   * @throws None
   */
  virtual void add() = 0;

  /**
   * Called when the event is removed from the event manager.
   *
   * @throws None
   */
  virtual void remove() = 0;
  virtual void process() = 0;

private:
  unsigned int m_cycle{};
  unsigned int m_nextTick{};
  bool m_isActive{};
};

class EventManager {
public:
  static EventManager &getInstance() {
    static EventManager instance;
    return instance;
  }

  void addEvent(Event *event) {
    // Ensure the event is not already added.
    if (std::find(m_eventQueue.begin(), m_eventQueue.end(), event) == m_eventQueue.end()) {
      // m_eventQueue.push_back(event);

      // Add as ordered
      auto it =
          std::lower_bound(m_eventQueue.begin(), m_eventQueue.end(), event,
                           [](const Event *lhs, const Event *rhs) { return lhs->getNextTick() < rhs->getNextTick(); });
      m_eventQueue.insert(it, event);

      event->add();
    }
  }

  void removeEvent(Event *event) {
    auto it = std::find(m_eventQueue.begin(), m_eventQueue.end(), event);
    if (it != m_eventQueue.end()) {
      m_eventQueue.erase(it);
      event->remove();
    }
  }

  std::vector<Event *> getEventQueue() const { return m_eventQueue; }

private:
  EventManager() = default;

  std::vector<Event *> m_eventQueue;
};