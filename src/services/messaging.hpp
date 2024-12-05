#pragma once

#include <iostream> // TODO(renda): Remove after testing
#include <string>
#include <thread>
#include <zmq.hpp>

#include "services/serviceContainer.hpp"

constexpr int MESSAGING_THREAD_SLEEP_DURATION = 100;
constexpr int MESSAGING_NO_CONNECTION_SLEEP_DURATION = 1000;
constexpr int MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION = 100;

class Messaging {
public:
  Messaging()
      : m_publisherContext(new zmq::context_t(1)),
        m_publisher(new zmq::socket_t(*m_publisherContext, zmq::socket_type::pub)),
        m_commandReceiverContext(new zmq::context_t(1)),
        m_commandReceiver(new zmq::socket_t(*m_commandReceiverContext, zmq::socket_type::pair)) {
    m_publisher->bind("tcp://*:12345");
    m_publisherThread = std::thread([&] { messagingStep(); });

    m_commandReceiver->bind("tcp://*:12340");
    m_commandReceiverThread = std::thread([&] { commandReceiverStep(); });

    std::cout << "Messaging initialized" << std::endl; // TODO(renda): Remove after testing
  }

  ~Messaging() {
    m_isPublisherThreadRunning = false;

    if (m_publisherThread.joinable()) {
      m_publisherThread.join();
    }

    delete m_publisher;
    delete m_publisherContext;
  }

private:
  void messagingStep() {
    while (m_isPublisherThreadRunning) {
      try {
        long simTime = ServiceContainer::timer().simMillis();
        double timeInSeconds = static_cast<double>(simTime) / 1000;

        std::string timeStr = std::to_string(timeInSeconds);
        timeStr = timeStr.substr(0, timeStr.find('.') + 3); // Keep 2 decimal places
        zmq::message_t message(timeStr.data(), timeStr.size());
        m_publisher->send(zmq::str_buffer("SIM_TIME"), zmq::send_flags::sndmore);
        m_publisher->send(message, zmq::send_flags::none);

        std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_THREAD_SLEEP_DURATION));
      } catch (std::exception const &e) {
        std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_NO_CONNECTION_SLEEP_DURATION));
        continue; // Waiting for a connection
      }
    }
  }

  void commandReceiverStep() {
    while (m_isCommandReceiverThreadRunning) {
      std::array<char, 1024> buf{'\0'};
      zmq::mutable_buffer request(buf.data(), buf.size());
      zmq::recv_buffer_result_t result = m_commandReceiver->recv(request, zmq::recv_flags::none);

      std::string command = static_cast<char *>(request.data());

      std::cout << "Received: " << command << std::endl; // TODO(renda): Remove after testing

      if (command == "START") {
        ServiceContainer::getInstance().scheduler()->start();
      } else if (command == "STOP") {
        ServiceContainer::getInstance().scheduler()->stop();
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION));
    }
  }

  zmq::context_t *m_publisherContext;
  zmq::socket_t *m_publisher;
  std::thread m_publisherThread;
  bool m_isPublisherThreadRunning = true;

  zmq::context_t *m_commandReceiverContext;
  zmq::socket_t *m_commandReceiver;
  std::thread m_commandReceiverThread;
  bool m_isCommandReceiverThreadRunning = true;
};