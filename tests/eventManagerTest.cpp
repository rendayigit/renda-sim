#include "gtest/gtest.h"

#include "services/modelEvent.hpp"

TEST(EventManager, EventQueue) {
  ModelEvent evt1;
  evt1.setTriggerTime(1);
  evt1.activate();
  EventManager::getInstance().addEvent(&evt1);

  ModelEvent evt2;
  evt2.setTriggerTime(3);
  evt2.activate();
  EventManager::getInstance().addEvent(&evt2);

  ModelEvent evt3;
  evt3.setTriggerTime(2);
  evt3.activate();
  EventManager::getInstance().addEvent(&evt3);

  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(0)->getNextTick(), 1 * 1000000);
  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(1)->getNextTick(), 2 * 1000000);
  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(2)->getNextTick(), 3 * 1000000);
}