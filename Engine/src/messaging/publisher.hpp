#pragma once

#include <nlohmann/json.hpp>
#include <string>

#include <zmq.hpp>

class Publisher {
public:
  static Publisher &getInstance() {
    static Publisher instance;
    return instance;
  }

  void queueMessage(const std::string &topic, const std::string &message);
  void queueMessage(const std::string &topic, const nlohmann::json &jsonMessage);

  std::string getPort() const { return m_port; }

private:
  Publisher();
  ~Publisher();

  std::string m_port;
  zmq::context_t *m_context{};
  zmq::socket_t *m_socket{};
};