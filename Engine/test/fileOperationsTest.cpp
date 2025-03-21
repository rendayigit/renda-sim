#include "common.hpp"
#include <gtest/gtest.h>
#include <string_view>

// Returns true if the given string ends with "/bin/", else returns false.
bool endsWithBin(const std::string &inputStr) {
  std::string_view svInput(inputStr);

  const char *subStr = "/bin/";

  // Find the position where "/bin/" begins in original input string.
  auto pos = svInput.find(subStr);

  // If found "/bin/" at the end return true, else return false.
  return pos != std::string_view::npos && pos + strlen(subStr) == svInput.length();
}

TEST(FileOperations, GetExecutableDirectory) {
  std::string executableDirectory = getExecutableDirectory();

  // Check if the path ends with "/bin/"
  EXPECT_TRUE(endsWithBin(executableDirectory));
}