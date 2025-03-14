#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include "eventManager/eventManager.hpp"

class Scheduler : public boost::noncopyable {
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

  void execute(boost::system::error_code const &errorCode);
  void step(long currentMillis);
  void transmitTime(long simTimeMillis);

  EventManager *m_eventManagerInstance = &EventManager::getInstance();
  std::vector<Event *> *m_eventQueueInstance = EventManager::getInstance().getEventQueue();

  double m_stepTimeMicros{};
  double m_rate{};

  bool m_isRunning = false;

  long long m_lastStopTicks{};
  long m_progressTimeLastMillis{};

  boost::asio::io_service m_ioService;
  std::function<void(void)> m_task;
  boost::asio::deadline_timer m_timer;
  boost::asio::io_service::work m_work;
  std::thread m_workingThread;
};