#include "models/common/dataFlow.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

/* Defines */
const double aIn = 3.4;
const double aOut = 4.5;
const double bIn = 6.7;
const double bOut = 7.8;

TEST(DataFlow, SetAndGet) {
  InFlow<double> aInFlow;
  OutFlow<double> aOutFlow;

  aInFlow.setValue(aIn);
  aOutFlow.setValue(aOut);

  EXPECT_EQ(aInFlow.getValue(), aIn);
  EXPECT_EQ(aOutFlow.getValue(), aOut);
}

TEST(DataFlow, DefaultValues) {
  InFlow<double> aInFlow(aIn);
  OutFlow<double> aOutFlow(aOut);

  EXPECT_EQ(aInFlow.getValue(), aIn);
  EXPECT_EQ(aOutFlow.getValue(), aOut);
}

TEST(DataFlow, Connect) {
  InFlow<double> aInFlow;
  InFlow<double> bInFlow;
  OutFlow<double> aOutFlow;

  aInFlow.setValue(aIn);
  bInFlow.setValue(bIn);
  aOutFlow.setValue(aOut);

  EXPECT_EQ(aInFlow.getValue(), aIn);
  EXPECT_EQ(bInFlow.getValue(), bIn);
  EXPECT_EQ(aOutFlow.getValue(), aOut);

  aOutFlow.connect(&aInFlow);
  aOutFlow.connect(&bInFlow);

  aOutFlow.setValue(bOut);

  EXPECT_EQ(aInFlow.getValue(), bOut);
  EXPECT_EQ(bInFlow.getValue(), bOut);
  EXPECT_EQ(aOutFlow.getValue(), bOut);

  aOutFlow.setValue(aOut);

  EXPECT_EQ(aInFlow.getValue(), aOut);
  EXPECT_EQ(bInFlow.getValue(), aOut);
  EXPECT_EQ(aOutFlow.getValue(), aOut);
}

TEST(DataFlow, UpdateFunction) {
  InFlow<double> inFlow;
  OutFlow<double> outFlow;

  bool updateFunctionTestVariable = false;

  inFlow.setUpdateFunction([&](double) { updateFunctionTestVariable = true; });

  EXPECT_FALSE(updateFunctionTestVariable);

  inFlow.setValue(aIn);
  EXPECT_TRUE(updateFunctionTestVariable);
  EXPECT_EQ(inFlow.getValue(), aIn);

  updateFunctionTestVariable = false;
  outFlow.connect(&inFlow);
  outFlow.setValue(aOut);
  EXPECT_TRUE(updateFunctionTestVariable);
  EXPECT_EQ(inFlow.getValue(), aOut);
  EXPECT_EQ(outFlow.getValue(), aOut);
}

TEST(DataFlow, SumInFlowStates) {
  // Create sumInflow Object with default Value
  SumInFlow<double> sumInFlow(0);
  // Create OutflowA with default Value
  OutFlow<double> outFlowA(0);
  // Create OutflowB with default Value
  OutFlow<double> outFlowB(0);

  // Connect outFlowA to sumInflow
  outFlowA.connect(&sumInFlow);
  // Connect outFlowB to sumInflow
  outFlowB.connect(&sumInFlow);

  // Both flows are 0
  // Verify That outflowA value is 0
  EXPECT_EQ(0, outFlowA.getValue());
  // Verify That outflowB value is 0
  EXPECT_EQ(0, outFlowB.getValue());
  // Verify That sumInflow value is 0
  EXPECT_EQ(0, sumInFlow.getValue());

  // Flow A is aOut, sumInflow is aOut
  // Set outFlowA Value to aOut
  outFlowA.setValue(aOut);
  // Verify that outFlowA Value is aOut
  EXPECT_EQ(aOut, outFlowA.getValue());
  // Verify that outFlowB Value is stil 0
  EXPECT_EQ(0, outFlowB.getValue());
  // Verify That sumInflow value is aOut
  EXPECT_EQ(aOut, sumInFlow.getValue());

  // Flow A value is aOut, Flow b value is bOut, sumInflow value is aOut + bOut
  // Set OutFlowB to bOut
  outFlowB.setValue(bOut);
  // Verify that outFlowA Value is aOut
  EXPECT_EQ(aOut, outFlowA.getValue());
  // Verify that outFlowB Value is bOut
  EXPECT_EQ(bOut, outFlowB.getValue());
  // Verify that multInflow value is still aOut
  EXPECT_EQ(aOut + bOut, sumInFlow.getValue());

  // Loop through values for OutFlowA and OutFlowB to test interactions
  for (int currentAOut = 0; currentAOut < static_cast<int>(aOut); ++currentAOut) {
    for (int currentBOut = 0; currentBOut < static_cast<int>(bOut); ++currentBOut) {
      // Set the value of outFlowA to currentAOut
      outFlowA.setValue(static_cast<double>(currentAOut));

      // Set the value of outFlowB to currentBOut
      outFlowB.setValue(static_cast<double>(currentBOut));

      // Verify that outFlowA's value is as expected
      EXPECT_EQ(currentAOut, static_cast<int>(outFlowA.getValue()));

      // Verify that outFlowB's value is as expected
      EXPECT_EQ(currentBOut, static_cast<int>(outFlowB.getValue()));

      // Verify that the sumInFlow's value is the sum of outFlowA and outFlowB
      EXPECT_EQ(currentAOut + currentBOut, static_cast<int>(sumInFlow.getValue()));
    }
  }

  // Flow A value is 0, Flow B value is bOut, sumInflow  value is bOut
  // Set OutFlow A to 0
  outFlowA.setValue(0);
  // Set OutFlow B to bOut
  outFlowB.setValue(bOut);
  // Verify that outFlowA Value is 0
  EXPECT_EQ(0, outFlowA.getValue());
  // Verify that outFlowB Value is bOut
  EXPECT_EQ(bOut, outFlowB.getValue());
  // Verify that sumInflow value is bOut
  EXPECT_EQ(bOut, sumInFlow.getValue());

  // Both flow are 0
  // Set OutFlow B to 0
  outFlowB.setValue(0);
  // Verify that outFlowA Value is 0
  EXPECT_EQ(0, outFlowA.getValue());
  // Verify that outFlowB Value is 0
  EXPECT_EQ(0, outFlowB.getValue());
  // Verify that sumInflow value is 0
  EXPECT_EQ(0, sumInFlow.getValue());
}

TEST(DataFlow, SumInFlowUnconnectedOutflowUsage) {
  // Create sumInflowA Object with default Value
  SumInFlow<double> sumInflowA(0);
  // Set sumInflowA value to aIn
  sumInflowA.setValue(aIn);
  // Verify that sumInflowA value is aIn
  EXPECT_EQ(aIn, sumInflowA.getValue());
}

TEST(DataFlow, BadInflowUsage) {
  // Create InflowA Object with default Value
  InFlow<double> inflowA(0);
  // Create OutflowA with default Value
  OutFlow<double> outFlowA(0);
  // Create OutflowB with default Value
  OutFlow<double> outFlowB(0);
  // Create InflowC as nullPtr
  InFlow<double> *inflowB = nullptr;

  // Verify that connecting with a nullptr as InFlow throws an std::invalid_argument exception.
  EXPECT_THROW(outFlowA.connect(inflowB), std::invalid_argument);

  // Connect outFlowA to inflow
  outFlowA.connect(&inflowA);

  // Verify that connecting the same inFlow to multiple outFlows throws a std::logic_error
  // exception.
  EXPECT_THROW(outFlowB.connect(&inflowA), std::logic_error);

  // Verify that connecting the same outFlow and inFlow twice throws a std::logic_error exception
  EXPECT_THROW(outFlowA.connect(&inflowA), std::logic_error);
}