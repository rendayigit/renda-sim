#include <gtest/gtest.h>

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/scheduler/scheduler.hpp"

TEST(SimpleEvent, BasicFunctionality) {
  SimpleEvent event;

  // Verify the event is deactivated at startup
  EXPECT_FALSE(event.isActive());

  // Activate the event and verify it is active
  event.activate();
  EXPECT_TRUE(event.isActive());

  // Deactivate the event and verify it is not active
  event.deactivate();
  EXPECT_FALSE(event.isActive());
}

TEST(SimpleEvent, CyclicEventAdvancedFunctionality) {
  SimpleEvent cyclicEvent;

  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  // Set event function to progess a counter
  int cyclicCounter = 0;
  cyclicEvent.setEventFunction([&] { cyclicCounter++; });
  EXPECT_EQ(cyclicCounter, 0);

  // Set cycle time to 1 millisecond
  cyclicEvent.setCycleMillis(1);

  // Verify the cycle time is set correctly
  EXPECT_EQ(cyclicEvent.getCycleMillis(), 1);

  // Verify the cycle ticks is set correctly
  //   EXPECT_EQ(cyclicEvent.getCycleTicks(), cyclicEvent.getCycleTime() * exec_get_time_tic_value() - 1);

  // Activate the event
  cyclicEvent.activate();

  // Add event to the event manager
  eventManager.addEvent(&cyclicEvent);

  // Progress the simulation for one millisecond and verify if the event function was called once in millisecond 0 and
  // and again in millisecond 1
  scheduler.progressTime(1);
  EXPECT_EQ(cyclicCounter, 2);

  // Progress the simulation for another millisecond and verify if the event function was called again
  scheduler.progressTime(1);
  EXPECT_EQ(cyclicCounter, 3);
}

TEST(SimpleEvent, SingleShotEventAdvancedFunctionality) {
  SimpleEvent singleShotEvent;

  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  // Set event function to progess a counter
  int singleShotCounter = 0;
  singleShotEvent.setEventFunction([&] { singleShotCounter++; });
  EXPECT_EQ(singleShotCounter, 0);

  // Set the trigger time to 2 milliseconds
  singleShotEvent.setNextMillis(2);

  // Activate the event
  singleShotEvent.activate();

  // Add event to the event manager
  eventManager.addEvent(&singleShotEvent);

  // Progress the simulation for one millisecond and verify if the event function was not yet called
  scheduler.progressTime(1);
  EXPECT_EQ(singleShotCounter, 0);

  // Progress the simulation for another millisecond and verify if the event function was called
  scheduler.progressTime(1);
  EXPECT_EQ(singleShotCounter, 1);

  // Progress the simulation for a second and verify if the event function was not called again
  scheduler.progressTime(1000);
  EXPECT_EQ(singleShotCounter, 1);
}