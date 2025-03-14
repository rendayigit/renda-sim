#pragma once

#include <memory>
#include <thread>

#include <boost/asio.hpp>

#include <scheduler/Entrypoint.hpp>
#include <vector>

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

  void AddSimulationTimeEvent(EntryPoint *entryPoint, long simulationTime, long cycleTime, int repeat);

  void handleEvent(EntryPoint *entryPoint, long simulationTime, long cycleTime, int repeat);

private:
  Scheduler();

  void transmitTime();

  double m_stepTimeMicros{};
  double m_rate{};

  std::thread m_schedulerThread;
  bool m_isRunning = false;

  long long m_lastStopTicks{};
  long m_progressTimeLastMillis{};

  boost::asio::io_service m_ioService;
  boost::asio::io_service::work m_work;
  std::thread m_workingThread;

  std::vector<EntryPoint *> *m_entryPoints = new std::vector<EntryPoint *>;
};