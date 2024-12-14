#include "services/messaging/messaging.hpp"

#include <iostream> // TODO(renda): Remove after testing
#include <string>

#include "services/model/modelVariable.hpp"
#include "services/model/variableProperties.hpp"
#include "services/messaging/messageParser.hpp"
#include "services/model/modelContainer.hpp"

constexpr int MESSAGING_MAX_COMMAND_SIZE = 1024;
constexpr int MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION = 100;

Messaging::~Messaging() {
  m_isCommandReceiverThreadRunning = false;

  if (m_commandReceiverThread.joinable()) {
    m_commandReceiverThread.join();
  }

  delete m_publisher;
  delete m_publisherContext;
}

void Messaging::queueMessage(const std::string &topic, const std::string &message) {
  zmq::message_t zTopic(topic.data(), topic.size());
  zmq::message_t zMessage(message.data(), message.size());

  m_publisher->send(zTopic, zmq::send_flags::sndmore);
  m_publisher->send(zMessage, zmq::send_flags::none);
}

void Messaging::reply(const std::string &message) { m_commandReceiver->send(zmq::buffer(message)); }

void Messaging::commandReceiverStep() {
  while (m_isCommandReceiverThreadRunning) {
    std::array<char, MESSAGING_MAX_COMMAND_SIZE> buf{'\0'};
    zmq::mutable_buffer request(buf.data(), buf.size());
    zmq::recv_buffer_result_t result = m_commandReceiver->recv(request, zmq::recv_flags::none);

    std::string command = static_cast<char *>(request.data());

    std::cout << "Received: " << command << std::endl; // TODO(renda): Remove after testing

    MessageParser::getInstance().executeCommand(command);

    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION));
  }
}