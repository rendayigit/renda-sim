#pragma once

#include <thread>
#include <zmq.hpp>

class Commanding {
public:
  static Commanding &getInstance() {
    static Commanding instance;
    return instance;
  }

  void start();
  void stop();

  void reply(const std::string &message);

  std::string getPort() const { return m_port; }

private:
  Commanding();
  ~Commanding();

  void step();

  std::string m_port;
  zmq::context_t *m_context{};
  zmq::socket_t *m_socket{};

  std::thread m_thread;
  bool m_isRunning{};
};