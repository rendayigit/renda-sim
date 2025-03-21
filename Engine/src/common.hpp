#pragma once

#include <climits>
#include <filesystem>
#include <linux/limits.h>
#include <string>
#include <unistd.h>

static std::string getExecutableDirectory() {
  char result[PATH_MAX]; // NOLINT(hicpp-avoid-c-arrays, modernize-avoid-c-arrays,
                         // cppcoreguidelines-avoid-c-arrays)

  // Get the path of the executable
  (void)readlink("/proc/self/exe", result, PATH_MAX); // NOLINT(bugprone-unused-return-value)

  // Get the path of the executable's parent directory
  std::filesystem::path exePath(result);

  // Get the path of the executable's parent directory
  return (exePath.parent_path().string() + '/');
}

#ifndef UNIT_TEST
const std::string CONFIG_PATH = getExecutableDirectory() + "../config.json";
#else
const std::string CONFIG_PATH = getExecutableDirectory() + "../../config.json";
#endif