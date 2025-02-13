#pragma once

#include <thread>
#include <zmq.hpp>

class Messaging {
public:
  static Messaging &getInstance() {
    static Messaging instance;
    return instance;
  }

  ~Messaging();

  void start();
  void stop();

  void queueMessage(const std::string &topic, const std::string &message);

  void reply(const std::string &message);

private:
  explicit Messaging()
      : m_publisherContext(new zmq::context_t(1)),
        m_publisher(new zmq::socket_t(*m_publisherContext, zmq::socket_type::pub)),
        m_commandReceiverContext(new zmq::context_t(1)),
        m_commandReceiver(new zmq::socket_t(*m_commandReceiverContext, zmq::socket_type::pair)) {
    m_publisher->bind("tcp://*:12345");       // TODO(renda): use a port number from the config file
    m_commandReceiver->bind("tcp://*:12340"); // TODO(renda): use a port number from the config file
    m_commandReceiver->set(zmq::sockopt::rcvtimeo,
                           100); // Set timeout to 100ms // TODO(renda): use a port number from the config file
  }

  void commandReceiverStep();

  zmq::context_t *m_publisherContext;
  zmq::socket_t *m_publisher;

  zmq::context_t *m_commandReceiverContext;
  zmq::socket_t *m_commandReceiver;
  std::thread m_commandReceiverThread;
  bool m_isCommandReceiverThreadRunning{};
};