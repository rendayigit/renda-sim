#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/core/noncopyable.hpp>
#include <mutex>
#include <nlohmann/json.hpp>
#include <thread>
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
  void step();
  void setRate(double rate);
  void progressSim(long millis);
  void reset();

  bool isRunning() const { return m_isRunning; }

private:
  Scheduler();

  void execute(boost::system::error_code const &errorCode);
  void transmitTime(long simTimeMillis);

  EventManager *m_eventManagerInstance = &EventManager::getInstance();
  std::vector<Event *> *m_eventQueueInstance = EventManager::getInstance().getEventQueue();

  long m_currentMillis{};

  double m_rate = 1.0;

  bool m_isRunning = false;

  boost::asio::io_service m_ioService;
  boost::asio::deadline_timer m_schedulerTimer;
  boost::asio::deadline_timer m_durationTimer;
  boost::asio::io_service::work m_work;
  std::thread m_workingThread;

  std::mutex m_mutex;
};