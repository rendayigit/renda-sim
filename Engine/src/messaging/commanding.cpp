#include "messaging/commanding.hpp"

#include <nlohmann/json.hpp>
#include <string>

#include "logger/logger.hpp"
#include "messaging/commandParser.hpp"

constexpr int MAX_CONTEXT_THREAD_COUNT = 1;
constexpr int MAX_COMMAND_SIZE = 1024;
constexpr int RECEIVER_SLEEP_DURATION = 100;
constexpr int BINDING_DELAY = 200;
constexpr int SOCKET_TIMEOUT = 100;

Commanding::Commanding()
    : m_port("12340"), // TODO: Get from config file
      m_context(new zmq::context_t(MAX_CONTEXT_THREAD_COUNT)),
      m_socket(new zmq::socket_t(*m_context, zmq::socket_type::rep)) {
  try {
    m_socket->bind("tcp://0.0.0.0:" + m_port);
    std::this_thread::sleep_for(std::chrono::milliseconds(BINDING_DELAY)); // Minor sleep to allow the socket to bind
    m_socket->set(zmq::sockopt::rcvtimeo, SOCKET_TIMEOUT); // Set timeout to 100ms // TODO: Get from config file
  } catch (zmq::error_t &e) {
    Logger::critical("Zmq commanding error: " + std::string(e.what()));
  }
}

Commanding::~Commanding() {
  stop();

  delete m_socket;
  delete m_context;
}

void Commanding::start() {
  m_isRunning = true;
  m_thread = std::thread([&] { step(); });
}

void Commanding::stop() {
  m_isRunning = false;

  if (m_thread.joinable()) {
    m_thread.join();
  }
}

void Commanding::reply(const std::string &message) {
  Logger::debug("Replying: " + message);

  m_socket->send(zmq::buffer(message), zmq::send_flags::none);
}

void Commanding::step() {
  while (m_isRunning) {
    std::array<char, MAX_COMMAND_SIZE> buf{'\0'};
    zmq::mutable_buffer request(buf.data(), buf.size());
    zmq::recv_buffer_result_t result = m_socket->recv(request, zmq::recv_flags::none);

    std::string command = static_cast<char *>(request.data());

    if (command.empty()) {
      continue; // Skip empty
    }

    Logger::debug("Received command: " + command);

    CommandParser::getInstance().executeCommand(nlohmann::json::parse(command));

    std::this_thread::sleep_for(std::chrono::milliseconds(RECEIVER_SLEEP_DURATION));
  }
}