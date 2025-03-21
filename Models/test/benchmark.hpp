#pragma once

#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>

/**
 * @brief Prints a message
 *
 * @param message The message to print
 */
#define TEST_COUT(message) ((std::cout << "[ BENCHMARK] " << (message) << std::endl))

/**
 * @brief Returns the current time in nanoseconds
 *
 * @return The current time in nanoseconds
 */
#define GET_TIME()                                                                                                     \
  (double)std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch())    \
      .count();

/**
 * @brief Returns the elapsed time
 *
 * @param timeStart The start time
 * @param timeEnd The end time
 * @return The elapsed time
 */
#define GET_ELAPSED_TIME(timeStart, timeEnd) ((double)timeEnd - (double)timeStart)

/**
 * @brief Benchmarks a function
 *
 * @param test_name The title of the test
 * @param test The test case name
 * @param func The function to benchmark
 */
#define TEST_BENCHMARK(test_name, test, func)                                                                          \
  uint64_t timeStart = GET_TIME();                                                                                     \
  int i = 0;                                                                                                           \
  int itr = 1000;                                                                                                      \
  for (; i < itr; i++) {                                                                                               \
    func;                                                                                                              \
  }                                                                                                                    \
  uint64_t timeEnd = GET_TIME();                                                                                       \
  double timeResult = GET_ELAPSED_TIME(timeStart, timeEnd);                                                            \
  std::string res;                                                                                                     \
  if (timeResult >= 1000000000) {                                                                                      \
    res = "Average Time : " + std::to_string(timeResult * pow(10, -9)) + " secs";                                      \
    TEST_COUT(res);                                                                                                    \
  } else if (timeResult >= 1000000) {                                                                                  \
    res = "Average Time : " + std::to_string(timeResult * pow(10, -6)) + " ms";                                        \
    TEST_COUT(res);                                                                                                    \
  } else if (timeResult >= 1000) {                                                                                     \
    res = "Average Time : " + std::to_string(timeResult * pow(10, -3)) + " μs";                                        \
    TEST_COUT(res);                                                                                                    \
  } else {                                                                                                             \
    res = "Average Time : " + std::to_string(timeResult) + " nsecs";                                                   \
    TEST_COUT(res);                                                                                                    \
  }
