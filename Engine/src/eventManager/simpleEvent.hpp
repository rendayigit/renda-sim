#pragma once

#include <functional>
#include <utility>

#include "event.hpp"

class SimpleEvent : public Event {
public:
  /**
   * Sets the event callback function for the event.
   *
   * @param eventFunction The function to be set as the event callback function.
   *
   * @throws None
   */
  void setEventFunction(std::function<void()> eventFunction) { m_eventFunction = std::move(eventFunction); }

private:
  void process() override { m_eventFunction(); }

  std::function<void()> m_eventFunction;
};