#include "logger.hpp"

#include "common.hpp"
#include "messaging/publisher.hpp"
#include <spdlog/spdlog.h>

void Logger::info(const std::string &message) {
  getConsoleLogger()->info(message);
  getFileLogger()->info(message);
  transmitLog("INFO", message);
}

void Logger::error(const std::string &message) {
  getConsoleLogger()->error(message);
  getFileLogger()->error(message);
  transmitLog("ERROR", message);
}

void Logger::warn(const std::string &message) {
  getConsoleLogger()->warn(message);
  getFileLogger()->warn(message);
  transmitLog("WARNING", message);
}

void Logger::critical(const std::string &message) {
  getConsoleLogger()->critical(message);
  getFileLogger()->critical(message);
  transmitLog("CRITICAL", message);
}

void Logger::debug(const std::string &message) {
  getConsoleLogger()->debug(message);
  getFileLogger()->debug(message);
  transmitLog("DEBUG", message);
}

void Logger::transmitLog(const std::string &logLevel, const std::string &log) {
  nlohmann::json message;
  message["level"] = logLevel;
  message["log"] = log;

  Publisher::getInstance().queueMessage("EVENT", message);
}

std::shared_ptr<spdlog::logger> Logger::getFileLogger() {
  static std::shared_ptr<spdlog::logger> logger = [] {
    static std::string filePathName = getExecutableDirectory() + "/Engine.log";
    auto log = spdlog::daily_logger_mt("ENGINE", filePathName, 0, 0);
    log->set_pattern("[%H:%M:%S.%f %z] [%n] [%l] [thread %t] %v");
    log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::trace);
    return log;
  }();

  return logger;
}

std::shared_ptr<spdlog::logger> Logger::getConsoleLogger() {
  static std::shared_ptr<spdlog::logger> logger = [] {
    auto log = spdlog::default_logger();
    log->set_pattern("[%H:%M:%S.%f %z] [%n] [%l] [thread %t] %v");
    log->set_level(spdlog::level::trace); // TODO dont log debug and trace in release mode
    log->flush_on(spdlog::level::trace);
    return log;
  }();

  return logger;
}
