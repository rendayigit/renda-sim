#include "engine/eventManager/eventManager.hpp"

void EventManager::addEvent(Event *event) {
  // Ensure the event is not already added.
  if (std::find(m_eventQueue->begin(), m_eventQueue->end(), event) == m_eventQueue->end()) {
    // Find position to insert event into the queue
    auto it =
        std::lower_bound(m_eventQueue->begin(), m_eventQueue->end(), event, [](const Event *lhs, const Event *rhs) {
          return lhs->getNextMillis() < rhs->getNextMillis();
        });

    // Insert event into the queue based on next tick
    m_eventQueue->insert(it, event);
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

