#include "common.hpp"
#include <gtest/gtest.h>
#include <string_view>

// Returns true if the given string ends with "/tests/bin/", else returns false.
bool endsWithTestsBin(const std::string &inputStr) {
  std::string_view svInput(inputStr);

  const char *subStr = "/bin/";

  // Find the position where "/tests/bin/" begins in original input string.
  auto pos = svInput.find(subStr);

  // If found "/tests/bin/" at the end return true, else return false.
  return pos != std::string_view::npos && pos + strlen(subStr) == svInput.length();
}

TEST(FileOperation, GetExecutableDirectory) {
  std::string executableDirectory = getExecutableDirectory();

  // Check if the path ends with "/tests/bin/"
  EXPECT_TRUE(endsWithTestsBin(executableDirectory));
}