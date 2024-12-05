#pragma once

#include <iostream> // TODO(renda): Remove after testing
#include <thread>
#include <zmq.hpp>

#include "services/serviceContainer.hpp"

constexpr int MESSAGING_THREAD_SLEEP_DURATION = 100;
constexpr int MESSAGING_NO_CONNECTION_SLEEP_DURATION = 1000;

class Messaging {
public:
  Messaging() : m_context(new zmq::context_t(1)), m_publisher(new zmq::socket_t(*m_context, zmq::socket_type::pub)) {
    m_publisher->bind("tcp://*:12345");
    m_messagingThread = std::thread([&] { messagingStep(); });
    std::cout << "Messaging initialized" << std::endl; // TODO(renda): Remove after testing
  }

  ~Messaging() {
    m_isMessagingThreadRunning = false;

    if (m_messagingThread.joinable()) {
      m_messagingThread.join();
    }

    delete m_publisher;
    delete m_context;
  }

private:
  void messagingStep() {
    while (m_isMessagingThreadRunning) {
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

  zmq::context_t *m_context;
  zmq::socket_t *m_publisher;

  std::thread m_messagingThread;
  bool m_isMessagingThreadRunning = true;
};