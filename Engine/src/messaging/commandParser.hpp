#pragma once

#include <functional>
#include <map>
#include <nlohmann/json.hpp>
#include <string>

class CommandParser {
public:
  static CommandParser &getInstance() {
    static CommandParser instance;
    return instance;
  }

  void executeCommand(const nlohmann::json &command);

private:
  CommandParser();

  std::map<std::string, std::function<void(nlohmann::json)>> m_functionMap;
};