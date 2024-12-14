#include <iostream>
#include <string>

#include "logger.hpp"
#include "services/fileOperations/fileOperations.hpp"
#include "services/json/json.hpp"

const std::string CONFIG_PATH = FileOperations::getInstance().getExecutableDirectory() + "/../config.json";

Logger::Logger() {
  m_logger = spdlog::daily_logger_mt(
      "ENGINE", Json(CONFIG_PATH).getNode("LOGS_DIR").getValue<std::string>() + "Engine.log", 0, 0);
  m_logger->set_pattern("[%H:%M:%S.%f %z] [%n] [%l] [thread %t] %v");
}