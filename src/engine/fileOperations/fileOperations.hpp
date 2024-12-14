#pragma once

#include <string>

class FileOperations {
public:
  /**
   * @brief Get the FileOperations instance
   *
   * @return FileOperations singleton instance
   */
  static FileOperations &getInstance() {
    static FileOperations instance;
    return instance;
  }

  /**
   * @brief Get the executable directory
   *
   * @return The executable directory
   */
  std::string getExecutableDirectory() { return m_executableDirectory; }

private:
  FileOperations();

  std::string m_executableDirectory;
};
