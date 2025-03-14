#pragma once

#include <functional>
#include <utility>

class EntryPoint {
public:
  explicit EntryPoint(std::function<void(void)> event) : m_event(std::move(event)) {}
  void Execute() { m_event(); }

private:
  std::function<void(void)> m_event;
};
