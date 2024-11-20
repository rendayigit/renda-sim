#include "gtest/gtest.h"

#include "services/eventManager/simpleEvent.hpp"

TEST(EventManager, EventQueue) {
  SimpleEvent evt1;
  evt1.setNextTick(1);
  evt1.activate();
  EventManager::getInstance().addEvent(&evt1);

  SimpleEvent evt2;
  evt2.setNextTick(3);
  evt2.activate();
  EventManager::getInstance().addEvent(&evt2);

  SimpleEvent evt3;
  evt3.setNextTick(2);
  evt3.activate();
  EventManager::getInstance().addEvent(&evt3);

  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(0)->getNextTick(), 1);
  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(1)->getNextTick(), 2);
  EXPECT_EQ(EventManager::getInstance().getEventQueue().at(2)->getNextTick(), 3);
}