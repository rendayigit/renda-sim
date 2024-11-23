#pragma once
#include "services/network/client/client.hpp"
#include "services/network/server/server.hpp"

constexpr auto SERVER_ADDRESS = "127.0.0.1";
constexpr int SERVER_PORT = 12345;
constexpr int SLEEP_DURATION = 200;

class TestClient : public Client {
public:
  TestClient() = default;

  void onConnect() override { m_isConnectTriggered = true; }
  void onDisconnect() override { m_isDisconnectTriggered = true; }
  void onReceive(const std::string &message) override { m_lastReceivedMessage = message; }

  [[nodiscard]] bool isConnectTriggered() const { return m_isConnectTriggered; }
  [[nodiscard]] bool isDisconnectTriggered() const { return m_isDisconnectTriggered; }
  std::string getLastReceivedMessage() { return m_lastReceivedMessage; }

private:
  bool m_isConnectTriggered{};
  bool m_isDisconnectTriggered{};
  std::string m_lastReceivedMessage;
};

class TestServer : public Server {
public:
  explicit TestServer(uint16_t port) : Server(port) {}

  void onConnect(boost::asio::ip::tcp::socket * /*socket*/) override {
    m_isConnectTriggered = true;
  }

  void onDisconnect(boost::asio::ip::tcp::socket * /*socket*/) override {
    m_isDisconnectTriggered = true;
  }

  void onReceive(boost::asio::ip::tcp::socket * /*socket*/, const std::string &message) override {
    m_lastReceivedMessage = message;
  }

  [[nodiscard]] bool isConnectTriggered() const { return m_isConnectTriggered; }
  [[nodiscard]] bool isDisconnectTriggered() const { return m_isDisconnectTriggered; }
  std::string getLastReceivedMessage() { return m_lastReceivedMessage; }

private:
  bool m_isConnectTriggered{};
  bool m_isDisconnectTriggered{};
  std::string m_lastReceivedMessage;
};