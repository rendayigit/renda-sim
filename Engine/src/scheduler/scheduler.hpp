#pragma once

#include <thread>

class Scheduler {
public:
  static Scheduler &getInstance() {
    static Scheduler instance;
    return instance;
  }

  ~Scheduler();

  void start();
  void stop();
  void reset();

  void setRate(double rate);

  void progressTime(long millis);

  bool isRunning() const { return m_isRunning; }

private:
  Scheduler();

  void step(long currentMillis);
  void transmitTime(long simTimeMillis);

  double m_stepTimeMicros{};
  double m_rate{};

  std::thread m_schedulerThread;
  bool m_isRunning = false;

  long long m_lastStopTicks{};
  long m_progressTimeLastMillis{};
};