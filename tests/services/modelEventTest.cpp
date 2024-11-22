#include "services/modelEvent.hpp"
#include "mocks/EventManager_c_intf/mock_EventManager_c_intf.hpp"
#include "mocks/exec_proto/mock_exec_proto.hpp"
#include <gtest/gtest.h>

/**
 *@brief Test for ModelEvent class
 *@details These tests only test the mocked functions. The unit tests cannot run the trick simulator.
 */

TEST(ModelEvent, basicFeatures) {
  ModelEvent event;

  // Verify the event is deactivated at startup
  EXPECT_FALSE(event.isActive());

  // Activate the event and verify if it is active
  event.activate();
  EXPECT_TRUE(event.isActive());

  // Deactivate the event and verify if it is deactivated
  event.deactivate();
  EXPECT_FALSE(event.isActive());
}

TEST(ModelEvent, advancedFeatures) {
  // Create test events
  auto *cyclicEvent = new ModelEvent;
  auto *singleShotEvent = new ModelEvent;

  // Set event function to progess a counter
  int cyclicCounter = 0;
  cyclicEvent->setEventFunction([&] { cyclicCounter++; });
  EXPECT_EQ(cyclicCounter, 0);

  // Set cycle time to 1 second
  cyclicEvent->setCycleTime(1);

  // Verify the cycle time is set correctly
  EXPECT_EQ(cyclicEvent->getCycleTime(), 1);

  // Verify the cycle ticks is set correctly
  EXPECT_EQ(cyclicEvent->getCycleTicks(), cyclicEvent->getCycleTime() * exec_get_time_tic_value() - 1);

  // Activate the event
  cyclicEvent->activate();

  // Progress the simulation for one second and verify if the event function was called
  progressSimulation(1);
  EXPECT_EQ(cyclicCounter, 1);

  // Progress the simulation for another second and verify if the event function was called again
  progressSimulation(1);
  EXPECT_EQ(cyclicCounter, 2);

  // Reset the simulation time
  setSimTime(0.0);

  // Set event function to progess a counter
  int singleShotCounter = 0;
  singleShotEvent->setEventFunction([&] { singleShotCounter++; });
  EXPECT_EQ(singleShotCounter, 0);

  // Set the trigger time to 2 seconds
  singleShotEvent->setTriggerTime(2);

  // Activate the event
  singleShotEvent->activate();

  // Progress the simulation for one second and verify if the event function was not yet called
  progressSimulation(1);
  EXPECT_EQ(singleShotCounter, 0);

  // Progress the simulation for another second and verify if the event function was called
  progressSimulation(1);
  EXPECT_EQ(singleShotCounter, 1);

  // Cover event reset
  event_dummy_checkpoint_restart();
}