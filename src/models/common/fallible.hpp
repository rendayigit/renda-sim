#pragma once

#include "models/common/failure.hpp"
#include <optional>
#include <vector>

class Fallible {
public:
  /**
   * @brief Base class for all models that can fail in the simulation environment.
   *
   * @throws None
   */
  Fallible() = default;
  virtual ~Fallible() = default;

  // This virtual function is intended to return a boolean indicating whether the model is in a
  // failed state or not.
  virtual bool isFailed() = 0;

  // This virtual function is intended to return the list of all possible failures that the model
  // can trigger.
  virtual std::vector<Failure> getFailures() = 0;

  // This virtual function is intended to return the failure that the model has triggered if
  // `isFailed()` returns true. It should return `std::nullopt` if it is false.
  virtual std::optional<Failure> getFailure() = 0;
};