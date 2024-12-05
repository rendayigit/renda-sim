#pragma once

#include <iostream> // TODO(renda): Remove after testing
#include <string>
#include <thread>
#include <utility>
#include <vector>
#include <zmq.hpp>

#include "services/messageParser.hpp"
#include "services/serviceContainer.hpp"

constexpr int MESSAGING_MAX_COMMAND_SIZE = 1024;
constexpr int MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION = 100;

class Messaging {
public:
  static Messaging &getInstance() {
    static Messaging instance;
    return instance;
  }

  ~Messaging() {
    m_isCommandReceiverThreadRunning = false;

    if (m_commandReceiverThread.joinable()) {
      m_commandReceiverThread.join();
    }

    delete m_publisher;
    delete m_publisherContext;
  }

  void queueMessage(const std::string &topic, const std::string &message) {
    zmq::message_t zTopic(topic.data(), topic.size());
    zmq::message_t zMessage(message.data(), message.size());

    m_publisher->send(zTopic, zmq::send_flags::sndmore);
    m_publisher->send(zMessage, zmq::send_flags::none);
  }

  void reply(const std::string &message) { m_commandReceiver->send(zmq::buffer(message)); }

private:
  explicit Messaging()
      : m_publisherContext(new zmq::context_t(1)),
        m_publisher(new zmq::socket_t(*m_publisherContext, zmq::socket_type::pub)),
        m_commandReceiverContext(new zmq::context_t(1)),
        m_commandReceiver(new zmq::socket_t(*m_commandReceiverContext, zmq::socket_type::pair)) {
    m_publisher->bind("tcp://*:12345");
    m_commandReceiver->bind("tcp://*:12340");
    m_commandReceiverThread = std::thread([&] { commandReceiverStep(); });
  }

  void commandReceiverStep() {
    while (m_isCommandReceiverThreadRunning) {
      std::array<char, MESSAGING_MAX_COMMAND_SIZE> buf{'\0'};
      zmq::mutable_buffer request(buf.data(), buf.size());
      zmq::recv_buffer_result_t result = m_commandReceiver->recv(request, zmq::recv_flags::none);

      std::string command = static_cast<char *>(request.data());

      std::cout << "Received: " << command << std::endl; // TODO(renda): Remove after testing

      // TODO(renda): Move to MessageParser
      if (command == "STATUS") {
        Messaging::getInstance().reply("ENGINE ONLINE");
        continue;
      }

      MessageParser::getInstance().executeCommand(command);

      std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION));
    }
  }

  zmq::context_t *m_publisherContext;
  zmq::socket_t *m_publisher;

  zmq::context_t *m_commandReceiverContext;
  zmq::socket_t *m_commandReceiver;
  std::thread m_commandReceiverThread;
  bool m_isCommandReceiverThreadRunning = true;
};