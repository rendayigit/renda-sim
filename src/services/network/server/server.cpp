#include "server.hpp"
#include <iostream>
#include <utility>

#ifndef SWIG
namespace ip = boost::asio::ip;

Server::Server(uint16_t port) : m_ioThread(1), m_acceptor(m_ioContext, ip::tcp::endpoint(ip::tcp::v4(), port)) {
  doAccept();
}

Server::~Server() {
  if (not m_ioContext.stopped()) {
    m_ioContext.stop();
  }

  m_ioThread.join();
}

void Server::start() {
  try {
    post(m_ioThread, [this]() { m_ioContext.run(); });
  } catch (std::exception &e) {
    std::cerr << "Failed to start server: " << e.what() << '\n';
  }
}

void Server::stop() {
  try {
    for (auto *client : m_clients) {
      Session::removeClient(*this, client);
    }

    if (not m_ioContext.stopped()) {
      m_ioContext.stop();
      m_ioContext.restart();
    }
  } catch (std::exception &e) {
    std::cerr << "Failed to properly stop server: " << e.what() << '\n';
  }
}

void Server::doAccept() {
  m_acceptor.async_accept([this](boost::system::error_code errorCode, ip::tcp::socket socket) {
    if (not errorCode) {
      std::make_shared<Session>(this, std::move(socket))->run();
    } else if (errorCode == boost::asio::error::operation_aborted) {
      std::cout << "Server stopped\n";
    } else {
      std::cerr << "Error creating session: " << errorCode.message() << '\n';
    }

    doAccept();
  });
}

void Server::transmit(ip::tcp::socket *socket, const std::string &message) {
  if (socket->is_open()) {
    try {
      boost::asio::write(*socket, boost::asio::buffer(message));
    } catch (std::exception &e) {
      std::cerr << "Failed to transmit '" << message << "': " << e.what() << '\n';
    }
  } else {
    std::cerr << "Failed to transmit: Lost connection to client\n";
  }
}

void Server::broadcast(const std::string &message) {
  std::lock_guard<std::mutex> lock(m_clientsMutex);
  for (auto *client : m_clients) {
    transmit(client, message);
  }
}

void Server::onConnect(ip::tcp::socket *socket) {
  std::cout << socket->remote_endpoint().address().to_string() << " connected" << '\n';
}

void Server::onDisconnect(ip::tcp::socket *socket) {
  std::cout << socket->remote_endpoint().address().to_string() << " disconnected" << '\n';
}

void Server::onReceive(ip::tcp::socket *socket, const std::string &message) {
  std::cout << "Received: " << message << " from: " << socket->remote_endpoint().address().to_string() << '\n';
}

std::vector<ip::tcp::socket *> Server::getClients() const {
  std::lock_guard<std::mutex> lock(m_clientsMutex);
  return m_clients;
}

Session::Session(Server *server, ip::tcp::socket socket) : m_server(server), m_socket(std::move(socket)) {
  addClient(*m_server, &m_socket);
}

void Session::run() { scheduleRead(); }

void Session::addClient(Server &server, ip::tcp::socket *socket) {
  std::lock_guard<std::mutex> lock(server.m_clientsMutex);
  server.onConnect(socket);
  server.m_clients.push_back(socket);
}

void Session::removeClient(Server &server, ip::tcp::socket *socket) {
  std::lock_guard<std::mutex> lock(server.m_clientsMutex);
  server.onDisconnect(socket);

  if (socket->is_open()) {
    socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket->close();
  }

  server.m_clients.erase(std::remove(server.m_clients.begin(), server.m_clients.end(), socket), server.m_clients.end());
}

void Session::scheduleRead() {
  // TODO(renda): check if self is necessary
  auto self(shared_from_this());
  boost::asio::async_read_until(
      m_socket, m_buffer, "\0",
      [this, self](boost::system::error_code errorCode, std::size_t /*bytesTransferred*/) { readHandler(errorCode); });
}

void Session::readHandler(const boost::system::error_code &errorCode) {
  if (not errorCode) {
    std::string data{std::istreambuf_iterator<char>(&m_buffer), std::istreambuf_iterator<char>()};
    m_server->onReceive(&m_socket, data);
    scheduleRead();
  } else if (errorCode == boost::asio::error::eof) {
    removeClient(*m_server, &m_socket);
  } else if (errorCode == boost::asio::error::operation_aborted) {
    std::cout << "Server stopped\n";
  } else {
    std::cerr << "Error receiving from client: " << errorCode.message() << '\n';
  }
}
#endif