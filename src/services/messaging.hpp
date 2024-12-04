#pragma once

#include <iostream> // TODO(renda): Remove after testing
#include <thread>
#include <zmq.hpp>

constexpr int MESSAGING_THREAD_SLEEP_DURATION = 100;

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
        m_publisher->send(zmq::str_buffer("HEART_BEAT"), zmq::send_flags::sndmore);
        m_publisher->send(zmq::str_buffer("ENGINE IS LIVE"));

        std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_THREAD_SLEEP_DURATION));
      } catch (std::exception const &e) {
        continue; // Waiting for a connection
      }
    }
  }

  zmq::context_t *m_context;
  zmq::socket_t *m_publisher;

  std::thread m_messagingThread;
  bool m_isMessagingThreadRunning = true;
};