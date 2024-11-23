#include "services/logger/logger.hpp"
#include "benchmark.hpp"
#include "services/fileOperations.hpp"
#include <gtest/gtest.h>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem.hpp>
#include <filesystem>
#include <sstream>
#include <string>
#include <thread>

#define THREAD_LOG_COUNT 100

namespace fs = boost::filesystem;

// The local date and time
std::string getLocalTime() {
  return boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());
}

// The local date
std::string localDate = boost::gregorian::to_simple_string(boost::posix_time::second_clock::local_time().date());

std::string defaultLogFile = FileOperations::getInstance().getExecutableDirectory() + localDate + ".log";
std::string customLogFile = FileOperations::getInstance().getExecutableDirectory() + "/customLogFile.log";
std::string threadTestLogFile = FileOperations::getInstance().getExecutableDirectory() + "/threadTestLogFile.log";
std::string faultyTestLogFile = FileOperations::getInstance().getExecutableDirectory() + "/logs/faultyTestLogFile.log";
std::string faultyTestLogDirectory = FileOperations::getInstance().getExecutableDirectory() + "/logs/";

std::string thread1testLog = "Concurrent logger write test thread 1, log ";
std::string thread2testLog = "Concurrent logger write test thread 2, log ";

// Return the expected log stream
std::stringstream getExpectedStream() {
  // Expected log data string stream
  std::stringstream expectedLogStream;

  // Construct the expected log entries
  expectedLogStream << getLocalTime() + " INFO test info log 1\n";
  expectedLogStream << getLocalTime() + " INFO test info log 2\n";
  expectedLogStream << getLocalTime() + " ERROR test error log 1\n";
  expectedLogStream << getLocalTime() + " ERROR test error log 2\n";
  expectedLogStream << getLocalTime() + " WARNING test warning log 1\n";
  expectedLogStream << getLocalTime() + " WARNING test warning log 2\n";

  return expectedLogStream;
}

// Return the expected faulty log stream
std::stringstream getExpectedFaultyStream() {
  // Expected log data string stream
  std::stringstream expectedFaultyLogStream;

  // Construct the expected log entries
  expectedFaultyLogStream << getLocalTime() + " WARNING test warning log 1\n";
  expectedFaultyLogStream << getLocalTime() + " WARNING test warning log 2\n";

  return expectedFaultyLogStream;
}

// Thread 1 to write log entries to the log file concurrently
void writeThreadFirst() {
  Logger logger(threadTestLogFile);
  for (int i = 0; i < THREAD_LOG_COUNT; i++) {
    logger.log(LogLevel::LOG_INFO, thread1testLog + std::to_string(i));
  }
}

// Thread 2 to write log entries to the log file concurrently
void writeThreadSecond() {
  Logger logger(threadTestLogFile);
  for (int i = THREAD_LOG_COUNT; i < THREAD_LOG_COUNT * 2; i++) {
    logger.log(LogLevel::LOG_INFO, thread2testLog + std::to_string(i));
  }
}

// Return the log stream from the log file
std::stringstream getLogStream(const std::string &logFile) {
  // Stream to read the log file contents
  std::ifstream logBuffer;

  // Open the log file if it's not already open
  if (not logBuffer.is_open()) {
    logBuffer.open(logFile, std::ios::in);
  }

  // String stream to store the log file contents
  std::stringstream logStream;

  // Read the contents of the log file if it was successfully opened
  if (logBuffer.is_open()) {
    logStream << logBuffer.rdbuf();
    logBuffer.close();
  }

  return logStream;
}

TEST(Logger, NominalUsage) {
  // Remove test log file
  (void)std::remove(defaultLogFile.c_str());

  // Default Logger instance
  Logger logger;

  // Log a few INFO messages
  logger.log(LogLevel::LOG_INFO, "test info log 1");
  logger.log(LogLevel::LOG_INFO, "test info log 2");

  // Log a few ERROR messages
  logger.log(LogLevel::LOG_ERROR, "test error log 1");
  logger.log(LogLevel::LOG_ERROR, "test error log 2");

  // Log a few WARNING messages
  logger.log(LogLevel::LOG_WARNING, "test warning log 1");
  logger.log(LogLevel::LOG_WARNING, "test warning log 2");

  // Verify that the log file was created
  EXPECT_TRUE(fs::exists(defaultLogFile));

  // Verify that the contents of the log file match the expected log data
  EXPECT_EQ(getLogStream(defaultLogFile).str(), getExpectedStream().str());

  // Remove test log file
  (void)std::remove(defaultLogFile.c_str());
}

TEST(Logger, CustomLogDir) {
  // Create a Logger instance with a custom log file path
  Logger logger(customLogFile);

  // Remove test log file
  (void)std::remove(customLogFile.c_str());

  // Log a few INFO messages
  logger.log(LogLevel::LOG_INFO, "test info log 1");
  logger.log(LogLevel::LOG_INFO, "test info log 2");

  // Log a few ERROR messages
  logger.log(LogLevel::LOG_ERROR, "test error log 1");
  logger.log(LogLevel::LOG_ERROR, "test error log 2");

  // Log a few WARNING messages
  logger.log(LogLevel::LOG_WARNING, "test warning log 1");
  logger.log(LogLevel::LOG_WARNING, "test warning log 2");

  // Verify that the log file was created
  EXPECT_TRUE(fs::exists(customLogFile));

  // Verify that the contents of the log file match the expected log data
  EXPECT_EQ(getLogStream(customLogFile).str(), getExpectedStream().str());

  // Remove test log file
  (void)std::remove(customLogFile.c_str());
}

TEST(Logger, ThreadSafety) {
  // Remove test log file
  (void)std::remove(threadTestLogFile.c_str());

  // Create two threads to write log entries to the log file concurrently
  std::thread first(writeThreadFirst);
  std::thread second(writeThreadSecond);

  // Wait for the threads to finish
  first.join();
  second.join();

  // Verify that the log file was created
  EXPECT_TRUE(fs::exists(threadTestLogFile));

  std::stringstream stream = getLogStream(threadTestLogFile);
  std::string line;
  int thread1LogCount = 0;
  int thread2LogCount = 0;

  // Iterate over lines in the stream
  while (std::getline(stream, line)) {
    // Check if the line contains given log
    if (line.find(thread1testLog) != std::string::npos) {
      thread1LogCount++;
    } else if (line.find(thread2testLog) != std::string::npos) {
      thread2LogCount++;
    }
  }

  EXPECT_EQ(thread1LogCount, THREAD_LOG_COUNT);
  EXPECT_EQ(thread2LogCount, THREAD_LOG_COUNT);

  // Remove test log file
  (void)std::remove(threadTestLogFile.c_str());
}

TEST(Logger, FaultyUsage) {
  // Remove log path
  (void)std::filesystem::remove_all(faultyTestLogDirectory.c_str());

  // Create a Logger pointer with a custom log file path
  auto *logger = new Logger(faultyTestLogFile);

  // Log a few INFO messages
  logger->log(LogLevel::LOG_INFO, "test info log 1");
  logger->log(LogLevel::LOG_INFO, "test info log 2");

  // Delete the Logger pointer
  delete logger;

  // Create a new Logger pointer
  logger = new Logger(faultyTestLogFile);

  // Remove log path
  (void)std::filesystem::remove_all(faultyTestLogDirectory.c_str());

  // Log a few ERROR messages
  logger->log(LogLevel::LOG_ERROR, "test error log 1");
  logger->log(LogLevel::LOG_ERROR, "test error log 2");

  // Remove log path
  (void)std::filesystem::remove_all(faultyTestLogDirectory.c_str());

  // Log a few WARNING messages
  logger->log(LogLevel::LOG_WARNING, "test warning log 1");
  logger->log(LogLevel::LOG_WARNING, "test warning log 2");

  // Flush the log buffer
  logger->flush();

  // Verify that the log file was created
  EXPECT_TRUE(fs::exists(faultyTestLogFile));

  // Verify that the contents of the log file match the expected log data
  EXPECT_EQ(getLogStream(faultyTestLogFile).str(), getExpectedFaultyStream().str());

  // Remove log path
  (void)std::filesystem::remove_all(faultyTestLogDirectory.c_str());
}

TEST(Logger, Benchmark) {
  // Create a default Logger instance
  Logger logger;

  // Benchmark the logging function
  TEST_BENCHMARK("Logger", "loggingManualBenchmark", logger.log(LogLevel::LOG_INFO, "benchmark test"));

  // Remove test log file
  (void)std::remove(threadTestLogFile.c_str());
}
