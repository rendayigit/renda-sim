#pragma once

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>
#include <string>

class Logger {
public:
  static void info(const std::string &message);
  static void error(const std::string &message);
  static void warn(const std::string &message);
  static void critical(const std::string &message);
  static void debug(const std::string &message);

private:
  Logger() = default;
  static void transmitLog(const std::string &logLevel, const std::string &log);
  static std::shared_ptr<spdlog::logger> getFileLogger();
  static std::shared_ptr<spdlog::logger> getConsoleLogger();
};
