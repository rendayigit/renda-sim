#pragma once

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/spdlog.h>

/**
 * Logger class
 */
class Logger {
public:
  static std::shared_ptr<spdlog::logger> &log() {
    static Logger instance;
    return instance.m_logger;
  }

  // TODO(renda): Logger does not flush on program exit
  ~Logger() { m_logger->flush(); }

private:
  Logger();
  std::shared_ptr<spdlog::logger> m_logger;
};