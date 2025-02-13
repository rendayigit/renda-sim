#pragma once

#include <vector>

#include "event.hpp"

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