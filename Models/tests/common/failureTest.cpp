#include <gtest/gtest.h>

#include "common/failure.hpp"
#include "common/fallible.hpp"

// Derived test model from Fallible, implementing necessary virtual functions and logic
class FallibleTestModel : public Fallible {
public:
  FallibleTestModel() {
    // Initialize a sample failure with specific callbacks and checks
    m_sampleFailure = new Failure(
        "sample failure",
        [this]() {
          // must point to `fail()` function
          fail();
        },
        [this]() {
          // must point to `unfail()` function
          unfail();
        },
        [this]() {
          // must point to `isFailed()` function
          return isFailed();
        });

    // Add the sample failure to the list of failures
    m_failureList.push_back(*m_sampleFailure);
  }

  /* some logic that model renders when failed */
  void fail() {
    m_currentFailure = m_sampleFailure; // Assign current failure pointer to sample failure
    m_failState = true;                 // Set internal fail state to true
  }

  /* nominal mode logic that model renders when not failed */
  void unfail() {
    m_failState = false; // Set internal fail state to false
  }

  bool isFailed() override { return m_failState; }

  std::optional<Failure> getFailure() override {
    if (m_failState) {
      return *m_currentFailure; // Return the current failure
    }

    return std::nullopt; // Return null optional if no failure has occurred
  }

  std::vector<Failure> getFailures() override { return m_failureList; }

private:
  Failure *m_sampleFailure = nullptr;  // Pointer to a sample failure instance
  Failure *m_currentFailure = nullptr; // Pointer to the current active failure, if any
  bool m_failState{};                  // Boolean flag indicating whether the model is in a failed state or not
  std::vector<Failure> m_failureList;  // List of all possible failures for this model
};

TEST(Failure, Generic) {
  // Create an instance of the test model
  FallibleTestModel fallibleTestModel;

  // Verify there is one failure in the list of failures
  EXPECT_EQ(fallibleTestModel.getFailures().size(), 1);

  // Verify the name of the first failure matches expected value
  EXPECT_EQ(fallibleTestModel.getFailures().at(0).getName(), "sample failure");

  // Initially, expect the model is not failed
  EXPECT_FALSE(fallibleTestModel.isFailed());

  // Trigger the sample failure in the model
  fallibleTestModel.fail();

  // Verify the model is now failed after triggering failure
  EXPECT_TRUE(fallibleTestModel.isFailed());

  // Verify the model failure is set correctly in failed state
  EXPECT_EQ(fallibleTestModel.getFailure()->getName(), "sample failure");

  // Revert the model to nominal state
  fallibleTestModel.unfail();

  // Verify the model is not in failed state after reverting failure
  EXPECT_FALSE(fallibleTestModel.isFailed());

  // Verify the model failure returns null in nominal state
  EXPECT_EQ(fallibleTestModel.getFailure(), std::nullopt);
}