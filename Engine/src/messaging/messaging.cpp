#include "messaging/messaging.hpp"

#include <string>

#include "logger/logger.hpp"
#include "messaging/messageParser.hpp"

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

void Messaging::start() {
  m_isCommandReceiverThreadRunning = true;
  m_commandReceiverThread = std::thread([&] { commandReceiverStep(); });
}

void Messaging::stop() {
  m_isCommandReceiverThreadRunning = false;

  if (m_commandReceiverThread.joinable()) {
    m_commandReceiverThread.join();
  }
}

void Messaging::queueMessage(const std::string &topic, const std::string &message) {
  zmq::message_t zTopic(topic.data(), topic.size());
  zmq::message_t zMessage(message.data(), message.size());

  if (topic != "SIM_TIME") {
    Logger::log()->debug("Queuing: [" + topic + "] " + message);
  }

  m_publisher->send(zTopic, zmq::send_flags::sndmore);
  m_publisher->send(zMessage, zmq::send_flags::none);
}

void Messaging::reply(const std::string &message) {
  Logger::log()->debug("Replying: " + message);

  m_commandReceiver->send(zmq::buffer(message));
}

void Messaging::commandReceiverStep() {
  while (m_isCommandReceiverThreadRunning) {
    std::array<char, MESSAGING_MAX_COMMAND_SIZE> buf{'\0'};
    zmq::mutable_buffer request(buf.data(), buf.size());
    zmq::recv_buffer_result_t result = m_commandReceiver->recv(request, zmq::recv_flags::none);

    std::string command = static_cast<char *>(request.data());

    Logger::log()->debug("Received command: " + command);

    MessageParser::getInstance().executeCommand(command);

    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION));
  }
}