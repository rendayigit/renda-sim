#include "services/timer/timer.hpp"

double Timer::currentMillis() {
  auto now = std::chrono::high_resolution_clock::now();
  auto currentMillis = std::chrono::duration<double, std::milli>(now - m_initialTime).count();
  return currentMillis;
}