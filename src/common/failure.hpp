#pragma once

#include <functional>
#include <string>
#include <utility>

class Failure {
public:
  /**
   * @brief Failures can be assinged to fallible models.
   *
   * @param name The name of the failure.
   * @param fail Function to trigger the failure.
   * @param unfail Function to undo/resolve the failure.
   * @param isFailed Check if the failure has occurred.
   */
  explicit Failure(std::string name, std::function<void()> fail, std::function<void()> unfail,
                   std::function<bool()> isFailed)
      : m_name(std::move(name)), m_fail(std::move(fail)), m_unfail(std::move(unfail)), m_isFailed(std::move(isFailed)) {
  }

  virtual ~Failure() = default;

  /**
   * @brief Get the name of the failure.
   *
   * @return The name of the failure as a string.
   */
  std::string getName() { return m_name; }

private:
  // The name of the failure.
  std::string m_name;

  // Function to trigger the failure.
  std::function<void()> m_fail;

  // Function to undo/resolve the failure.
  std::function<void()> m_unfail;

  // Check if the failure has occurred.
  std::function<bool()> m_isFailed;
};