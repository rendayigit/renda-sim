#pragma once

#include <chrono>

class Timer {
public:
  static Timer &getInstance() {
    static Timer instance;
    return instance;
  }

  long simMillis() const;
  long long simTicks() const;
  void updateInitialTicks(long long);
  void reset();

private:
  Timer() : m_initialTicks(std::chrono::high_resolution_clock::now().time_since_epoch().count()) {}

  long long m_initialTicks;
};