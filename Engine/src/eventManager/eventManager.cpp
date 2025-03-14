#include "eventManager/eventManager.hpp"

#include <algorithm>

EventManager::~EventManager() { m_eventQueue->clear(); }

void EventManager::addEvent(Event *event) {
  // Ensure the event is not already added.
  if (std::find(m_eventQueue->begin(), m_eventQueue->end(), event) == m_eventQueue->end()) {
    // Insert event into the queue
    m_eventQueue->push_back(event);
  }
}

void EventManager::removeEvent(Event *event) {
  // Find event
  auto it = std::find(m_eventQueue->begin(), m_eventQueue->end(), event);

  // Remove event from queue
  if (it != m_eventQueue->end()) {
    m_eventQueue->erase(it);
  }
}
