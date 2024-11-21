#include "gtest/gtest.h"

#include "services/eventManager/simpleEvent.hpp"
#include "services/scheduler/scheduler.hpp"

TEST(EventManager, EventQueue) {
  SimpleEvent evt1;
  evt1.setNextMillis(1);
  evt1.activate();
  EventManager::getInstance().addEvent(&evt1);

  SimpleEvent evt2;
  evt2.setNextMillis(3);
  evt2.activate();
  EventManager::getInstance().addEvent(&evt2);

  SimpleEvent evt3;
  evt3.setNextMillis(2);
  evt3.activate();
  EventManager::getInstance().addEvent(&evt3);

  // Test order
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(0)->getNextMillis(), 1);
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(1)->getNextMillis(), 2);
  EXPECT_EQ(EventManager::getInstance().getEventQueue()->at(2)->getNextMillis(), 3);
}

TEST(EventManager, SingleShotEventTriggering) {
  int triggerCount = 0;

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setNextMillis(3);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(triggerCount, 0);

  Scheduler::getInstance().progressTime(1);

  EXPECT_EQ(triggerCount, 0);

  Scheduler::getInstance().progressTime(2);

  EXPECT_EQ(triggerCount, 1);

  Scheduler::getInstance().progressTime(10000);

  EXPECT_EQ(triggerCount, 1);
}

TEST(EventManager, CyclicEventTriggering) {
  int triggerCount = 0;

  SimpleEvent evt;
  evt.setEventFunction([&] { triggerCount += 1; });
  evt.setCycleMillis(5);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(triggerCount, 0);

  Scheduler::getInstance().progressTime(1);

  EXPECT_EQ(triggerCount, 0);

  Scheduler::getInstance().progressTime(2);

  EXPECT_EQ(triggerCount, 0);

  Scheduler::getInstance().progressTime(3);

  EXPECT_EQ(triggerCount, 1);

  Scheduler::getInstance().progressTime(3);

  EXPECT_EQ(triggerCount, 1);

  Scheduler::getInstance().progressTime(2);

  EXPECT_EQ(triggerCount, 2);

  Scheduler::getInstance().progressTime(5);

  EXPECT_EQ(triggerCount, 3);

  Scheduler::getInstance().progressTime(5);

  EXPECT_EQ(triggerCount, 4);
}
