#include "gtest/gtest.h"

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/scheduler/scheduler.hpp"

TEST(EventManager, BasicEventFunctionality) {
  SimpleEvent event;

  // Verify the event is deactivated at startup
  EXPECT_FALSE(event.isActive());

  // Activate the event and verify it is active
  event.activate();
  EXPECT_TRUE(event.isActive());

  // Deactivate the event and verify it is not active
  event.deactivate();
  EXPECT_FALSE(event.isActive());

  // TODO(renda): test the rest of the event public functions
}

TEST(EventManager, EventQueue) {
  EventManager eventManager;

  SimpleEvent evt1;
  evt1.setNextMillis(1);
  evt1.activate();
  eventManager.addEvent(&evt1);

  SimpleEvent evt2;
  evt2.setNextMillis(3);
  evt2.activate();
  eventManager.addEvent(&evt2);

  SimpleEvent evt3;
  evt3.setNextMillis(2);
  evt3.activate();
  eventManager.addEvent(&evt3);

  // Test order
  EXPECT_EQ(eventManager.getEventQueue()->at(0)->getNextMillis(), 1);
  EXPECT_EQ(eventManager.getEventQueue()->at(1)->getNextMillis(), 2);
  EXPECT_EQ(eventManager.getEventQueue()->at(2)->getNextMillis(), 3);
}

TEST(EventManager, SingleShotEvents) {
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

TEST(EventManager, CyclicEvents) {
  SimpleEvent cyclicEvent;

  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  // Set event function to progess a counter
  int cyclicCounter = 0;
  cyclicEvent.setEventFunction([&] { cyclicCounter++; });
  EXPECT_EQ(cyclicCounter, 0);

  // Set cycle time to 5 milliseconds
  cyclicEvent.setCycleMillis(5);

  // Set next trigger time to 5 milliseconds
  cyclicEvent.setNextMillis(5);

  // Verify the cycle time is set correctly
  EXPECT_EQ(cyclicEvent.getCycleMillis(), 5);

  // Verify the cycle ticks is set correctly
  // TODO(renda): implement
  //   EXPECT_EQ(cyclicEvent.getCycleTicks(), cyclicEvent.getCycleTime() * exec_get_time_tic_value() - 1);

  // Activate the event
  cyclicEvent.activate();

  // Add event to the event manager
  eventManager.addEvent(&cyclicEvent);

  // Verify event is not yet triggered
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 1 millisecond and verify the event was is still not triggered
  scheduler.progressTime(1);
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 2 more milliseconds and verify the event is still not triggered
  scheduler.progressTime(2);
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 2 more milliseconds (making the time 5 milliseconds) and verify the event is triggered
  scheduler.progressTime(2);
  EXPECT_EQ(cyclicCounter, 1);

  // Progress the simulation by 3 more milliseconds and verify the event is not yet triggered a second time
  scheduler.progressTime(3);
  EXPECT_EQ(cyclicCounter, 1);

  // Progress the simulation by 2 more milliseconds and verify the event is triggered a second time
  scheduler.progressTime(2);
  EXPECT_EQ(cyclicCounter, 2);

  // Progress the simulation by 5 more milliseconds and verify the event is triggered a third time
  scheduler.progressTime(5);
  EXPECT_EQ(cyclicCounter, 3);

  // Progress the simulation by 4 more milliseconds and verify the event is not triggered a fourth time
  scheduler.progressTime(4);
  EXPECT_EQ(cyclicCounter, 3);
}

TEST(EventManager, NoTriggering) {
  int triggerCount = 0;
  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setNextMillis(5);
  evt.setCycleMillis(5);
  eventManager.addEvent(&evt);

  EXPECT_FALSE(evt.isActive());

  scheduler.progressTime(100);

  EXPECT_EQ(triggerCount, 0);
}