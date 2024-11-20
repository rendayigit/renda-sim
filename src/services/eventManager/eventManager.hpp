#pragma once

#include <algorithm>
#include <queue>
#include <vector>

class Event {
public:
  // Event() = default;
  // virtual ~Event();

  void setCycleMs(double milliseconds) { m_cycle = milliseconds * 1000000; }
  double getCycleMs() const { return m_cycle / 1000000; }

  void setCycleTicks(unsigned int ticks) { m_cycle = ticks; }
  unsigned int getCycleTicks() const { return m_cycle; }

  void setNextTick(unsigned int tick) { m_nextTick = tick; }
  unsigned int getNextTick() const { return m_nextTick; }

  void activate() { m_isActive = true; }
  void deactivate() { m_isActive = false; }
  bool isActive() const { return m_isActive; }

  virtual void add() = 0;
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