#pragma once

#include <functional>
#include <map>
#include <string>

#include "services/serviceContainer.hpp"

class MessageParser {
public:
  static MessageParser &getInstance() {
    static MessageParser instance;
    return instance;
  }

  void executeCommand(const std::string &command) {
    for (auto &function : m_functionMap) {
      if (command == function.first) {
        function.second("");
      }
    }
  }

private:
  MessageParser() {
    m_functionMap["START"] = [](const std::string & /*message*/) {
      ServiceContainer::getInstance().scheduler()->start();
    };

    m_functionMap["STOP"] = [](const std::string & /*message*/) {
      ServiceContainer::getInstance().scheduler()->stop();
    };

    m_functionMap["STATUS"] = [](const std::string & /*message*/) {
      // TODO(renda): Implement
      // Messaging::getInstance().reply("ENGINE ONLINE");
    };

    m_functionMap["SCHEDULER_STATUS"] = [](const std::string & /*message*/) {
      // TODO(renda): Implement
      // ServiceContainer::getInstance().scheduler()->isRunning()
    };
  }

  std::map<std::string, std::function<void(std::string)>> m_functionMap;
};