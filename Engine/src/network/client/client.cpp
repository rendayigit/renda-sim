#include "client.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/asio/read_until.hpp>
#include <cstdint>
#include <iostream>

namespace io = boost::asio;

Client::Client() : m_ioThread(1), m_ioWorker(m_ioContext), m_socket(m_ioContext) {}

Client::~Client() {
  if (not m_ioContext.stopped()) {
    m_ioContext.stop();
  }

  m_ioThread.join();
}

void Client::connect(const std::string &serverAddress, uint16_t serverPort) {
  if (isConnected()) {
    std::cerr << "Failed to connect: Already connected to server" << '\n';
    return;
  }

  post(m_ioThread, [this]() { m_ioContext.run(); });

  io::ip::tcp::resolver resolver(m_ioContext);
  io::ip::tcp::resolver::query query(serverAddress, std::to_string(serverPort));
  boost::system::error_code errorCode;

  io::connect(m_socket, resolver.resolve(query), errorCode);

  if (not errorCode) {
    onConnect();
    scheduleRead();
  } else {
    std::cerr << "Failed to connect: " << errorCode.message() << '\n';

    if (isConnected()) {
      m_socket.close();
    }
  }
}

void Client::disconnect() {
  try {
    if (isConnected()) {
      m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
      m_socket.close();
    }

    if (not m_ioContext.stopped()) {
      m_ioContext.stop();
      m_ioContext.restart();
    }
  } catch (std::exception &e) {
    std::cerr << "Failed to properly disconnect from server: " << e.what() << '\n';
  }
}

bool Client::isConnected() { return m_socket.is_open(); }

void Client::transmit(const std::string &message) {
  if (isConnected()) {
    try {
      io::write(m_socket, io::buffer(message));
    } catch (std::exception &e) {
      std::cerr << "Failed to transmit '" << message << "': " << e.what() << '\n';
    }
  } else {
    std::cerr << "Failed to transmit: Not connected\n";
  }
}

void Client::onDisconnect() {
  std::cout << "Disconnected from " << m_socket.remote_endpoint().address().to_string() << '\n';
}

void Client::onConnect() { std::cout << "Connected to " << m_socket.remote_endpoint().address().to_string() << '\n'; }

void Client::onReceive(const std::string &message) {
  std::cout << "Received: " << message << " from: " << m_socket.remote_endpoint().address().to_string() << '\n';
}

void Client::scheduleRead() {
  io::async_read_until(
      m_socket, m_buffer, "\0",
      [this](boost::system::error_code errorCode, std::size_t /*bytesTransferred*/) { readHandler(errorCode); });
}

void Client::readHandler(const boost::system::error_code &errorCode) {
  if (not errorCode) {
    std::string data{std::istreambuf_iterator<char>(&m_buffer), std::istreambuf_iterator<char>()};
    onReceive(data);
    scheduleRead();
  } else if (errorCode == boost::asio::error::eof) {
    std::cout << "Server disconnected\n";
    disconnect();
  } else if (errorCode == boost::asio::error::operation_aborted) {
    std::cout << "Connection aborted by client\n";
    disconnect();
  } else {
    std::cerr << "Error on connection: " << errorCode.message() << '\n';
    disconnect();
  }
}
