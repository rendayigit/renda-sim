#include "gtest/gtest.h"

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/scheduler/scheduler.hpp"

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

TEST(EventManager, SingleShotEventTriggering) {
  int triggerCount = 0;
  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setNextMillis(3);
  evt.activate();
  eventManager.addEvent(&evt);

  EXPECT_EQ(triggerCount, 0);

  scheduler.progressTime(1);

  EXPECT_EQ(triggerCount, 0);

  scheduler.progressTime(2);

  EXPECT_EQ(triggerCount, 1);

  scheduler.progressTime(10000);

  EXPECT_EQ(triggerCount, 1);
}

TEST(EventManager, CyclicEventTriggering) {
  int triggerCount = 0;
  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setNextMillis(5);
  evt.setCycleMillis(5);
  evt.activate();
  eventManager.addEvent(&evt);

  EXPECT_EQ(triggerCount, 0);

  scheduler.progressTime(1);

  EXPECT_EQ(triggerCount, 0);

  scheduler.progressTime(2);

  EXPECT_EQ(triggerCount, 0);

  scheduler.progressTime(3);

  EXPECT_EQ(triggerCount, 1);

  scheduler.progressTime(3);

  EXPECT_EQ(triggerCount, 1);

  scheduler.progressTime(2);

  EXPECT_EQ(triggerCount, 2);

  scheduler.progressTime(5);

  EXPECT_EQ(triggerCount, 3);

  scheduler.progressTime(5);

  EXPECT_EQ(triggerCount, 4);
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