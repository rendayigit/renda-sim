#include "publisher.hpp"

#include <chrono>
#include <thread>

#include "logger/logger.hpp"

constexpr int MAX_CONTEXT_THREAD_COUNT = 1;
constexpr int BINDING_DELAY = 200;

Publisher::Publisher()
    : m_port("12345"), // TODO: Get from config file
      m_context(new zmq::context_t(MAX_CONTEXT_THREAD_COUNT)),
      m_socket(new zmq::socket_t(*m_context, zmq::socket_type::pub)) {
  try {
    m_socket->bind("tcp://0.0.0.0:" + m_port);
    std::this_thread::sleep_for(std::chrono::milliseconds(BINDING_DELAY)); // Minor sleep to allow the socket to bind
  } catch (zmq::error_t &e) {
    Logger::critical("Zmq publish error: " + std::string(e.what()));
  }
}

Publisher::~Publisher() {
  delete m_socket;
  delete m_context;
}

void Publisher::queueMessage(const std::string &topic, const std::string &message) {
  zmq::message_t zTopic(topic.data(), topic.size());
  zmq::message_t zMessage(message.data(), message.size());

  m_socket->send(zTopic, zmq::send_flags::sndmore);
  m_socket->send(zMessage, zmq::send_flags::none);

  // m_socket->send(zmq::buffer(message), zmq::send_flags::none);
}

void Publisher::queueMessage(const std::string &topic, const nlohmann::json &jsonMessage) {
  std::string message = jsonMessage.dump();

  queueMessage(topic, message);
}