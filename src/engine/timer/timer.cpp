#include "engine/timer/timer.hpp"

long Timer::simMillis() const {
  return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::nanoseconds(simTicks())).count();
}

long long Timer::simTicks() const {
  return std::chrono::high_resolution_clock::now().time_since_epoch().count() - m_initialTicks;
}

void Timer::reset() { m_initialTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count(); }

void Timer::updateInitialTicks(long long lastTime) {
  m_initialTicks += (std::chrono::high_resolution_clock::now().time_since_epoch().count() - lastTime);
}
