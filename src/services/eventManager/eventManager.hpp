#pragma once

#include <algorithm>
#include <queue>
#include <vector>

class Event {
public:
  Event() = default;
  virtual ~Event();

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
  virtual void restart() = 0;
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
    m_eventQueue.emplace(event, event->getNextTick());
    event->add();
  }

  void removeEvent(Event *event) {
    // m_events.erase(std::find(m_events.begin(), m_events.end(), event));
    event->remove();
  }

private:
  EventManager() = default;

  std::priority_queue<Event *, std::vector<Event *>, std::less<>> m_eventQueue;
};