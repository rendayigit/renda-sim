#pragma once

#include <functional>
#include <map>
#include <string>

class MessageParser {
public:
  static MessageParser &getInstance() {
    static MessageParser instance;
    return instance;
  }

  void executeCommand(const std::string &command);

private:
  MessageParser();

  std::map<std::string, std::function<void(std::string)>> m_functionMap;
};