#include <iostream>
#include <string>

#include "fileOperations/fileOperations.hpp"
#include "logger.hpp"
#include "json/json.hpp"

const std::string CONFIG_PATH = FileOperations::getInstance().getExecutableDirectory() + "/../config.json";

Logger::Logger() {
  m_logger = spdlog::daily_logger_mt(
      "ENGINE", Json(CONFIG_PATH).getNode("LOGS_DIR").getValue<std::string>() + "Engine.log", 0, 0);
  m_logger->set_pattern("[%H:%M:%S.%f %z] [%n] [%l] [thread %t] %v");
  m_logger->set_level(spdlog::level::level_enum::trace); // TODO(renda): Activate only if in debug mode
}