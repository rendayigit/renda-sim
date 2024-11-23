#pragma once

#include <chrono>

class Timer {
public:
  static Timer &getInstance() {
    static Timer instance;
    return instance;
  }

  double currentMillis();

private:
  Timer() : m_initialTime(std::chrono::high_resolution_clock::now()) {}

  std::chrono::system_clock::time_point m_initialTime;
};