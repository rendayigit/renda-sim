#include "fileOperations/fileOperations.hpp"

#include <climits>
#include <filesystem>
#include <linux/limits.h>
#include <unistd.h>

FileOperations::FileOperations() {
  char result[PATH_MAX]; // NOLINT(hicpp-avoid-c-arrays, modernize-avoid-c-arrays,
                         // cppcoreguidelines-avoid-c-arrays)

  // Get the path of the executable
  (void)readlink("/proc/self/exe", result, PATH_MAX);

  // Get the path of the executable's parent directory
  std::filesystem::path exePath(result);

  // Get the path of the executable's parent directory
  m_executableDirectory = exePath.parent_path().string() + '/';

#ifdef UNIT_TEST
  // Return ./S_* executable path if running unit tests
  m_executableDirectory += "../../";
#endif
}
