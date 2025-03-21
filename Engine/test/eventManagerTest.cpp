#include "gtest/gtest.h"

#include "eventManager/eventManager.hpp"
#include "eventManager/simpleEvent.hpp"
#include "scheduler/scheduler.hpp"

TEST(EventManager, BasicEventFunctionality) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

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
  SimpleEvent evt1;
  evt1.setNextMillis(10);
  evt1.activate();
  EventManager::getInstance().addEvent(&evt1);

  SimpleEvent evt2;
  evt2.setNextMillis(30);
  evt2.activate();
  EventManager::getInstance().addEvent(&evt2);

  SimpleEvent evt3;
  evt3.setNextMillis(20);
  evt3.activate();
  EventManager::getInstance().addEvent(&evt3);

  // Test order
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(0)->getNextMillis(), 10);
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(1)->getNextMillis(), 30);
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(2)->getNextMillis(), 20);
}

TEST(EventManager, SingleShotEvents) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

  SimpleEvent singleShotEvent;

  // Set event function to progess a counter
  int singleShotCounter = 0;
  singleShotEvent.setEventFunction([&] { singleShotCounter++; });
  EXPECT_EQ(singleShotCounter, 0);

  // Set the trigger time to 2 milliseconds
  singleShotEvent.setNextMillis(20);

  // Activate the event
  singleShotEvent.activate();

  // Add event to the event manager
  EventManager::getInstance().addEvent(&singleShotEvent);

  // Progress the simulation for one millisecond and verify if the event function was not yet called
  Scheduler::getInstance().progressSim(10);
  EXPECT_EQ(singleShotCounter, 0);

  // Progress the simulation for another millisecond and verify if the event function was called
  Scheduler::getInstance().progressSim(10);
  EXPECT_EQ(singleShotCounter, 1);

  // Progress the simulation for 20ms and verify if the event function was not called again
  Scheduler::getInstance().progressSim(200);
  EXPECT_EQ(singleShotCounter, 1);
}

TEST(EventManager, CyclicEvents) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

  SimpleEvent cyclicEvent;

  // Set event function to progess a counter
  int cyclicCounter = 0;
  cyclicEvent.setEventFunction([&] { cyclicCounter++; });
  EXPECT_EQ(cyclicCounter, 0);

  // Set cycle time to 5 milliseconds
  cyclicEvent.setCycleMillis(50);

  // Set next trigger time to 5 milliseconds
  cyclicEvent.setNextMillis(50);

  // Verify the cycle time is set correctly
  EXPECT_EQ(cyclicEvent.getCycleMillis(), 50);

  // Verify the cycle ticks is set correctly
  // TODO(renda): implement
  //   EXPECT_EQ(cyclicEvent.getCycleTicks(), cyclicEvent.getCycleTime() * exec_get_time_tic_value() - 1);

  // Activate the event
  cyclicEvent.activate();

  // Add event to the event manager
  EventManager::getInstance().addEvent(&cyclicEvent);

  // Verify event is not yet triggered
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 1 millisecond and verify the event was is still not triggered
  Scheduler::getInstance().progressSim(10);
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 2 more milliseconds and verify the event is still not triggered
  Scheduler::getInstance().progressSim(20);
  EXPECT_EQ(cyclicCounter, 0);

  // Progress the simulation by 2 more milliseconds (making the time 5 milliseconds) and verify the event is triggered
  Scheduler::getInstance().progressSim(20);
  EXPECT_EQ(cyclicCounter, 1);

  // Progress the simulation by 3 more milliseconds and verify the event is not yet triggered a second time
  Scheduler::getInstance().progressSim(30);
  EXPECT_EQ(cyclicCounter, 1);

  // Progress the simulation by 2 more milliseconds and verify the event is triggered a second time
  Scheduler::getInstance().progressSim(20);
  EXPECT_EQ(cyclicCounter, 2);

  // Progress the simulation by 5 more milliseconds and verify the event is triggered a third time
  Scheduler::getInstance().progressSim(50);
  EXPECT_EQ(cyclicCounter, 3);

  // Progress the simulation by 4 more milliseconds and verify the event is not triggered a fourth time
  Scheduler::getInstance().progressSim(40);
  EXPECT_EQ(cyclicCounter, 3);
}

TEST(EventManager, NoTriggering) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

  int triggerCount = 0;

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setNextMillis(50);
  evt.setCycleMillis(50);
  EventManager::getInstance().addEvent(&evt);

  EXPECT_FALSE(evt.isActive());

  Scheduler::getInstance().progressSim(1000);

  EXPECT_EQ(triggerCount, 0);
}