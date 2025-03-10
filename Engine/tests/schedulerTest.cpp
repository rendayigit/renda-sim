#include <gtest/gtest.h>
#include <thread>

#include "eventManager/eventManager.hpp"
#include "eventManager/simpleEvent.hpp"
#include "scheduler/scheduler.hpp"

TEST(Scheduler, StartStop) {
  // Reset environment
  EventManager::getInstance().~EventManager();
  Scheduler::getInstance().~Scheduler();

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(0);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().start();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  Scheduler::getInstance().stop();

  int currentCount = count;

  EXPECT_GT(currentCount, 0);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_EQ(currentCount, count);
}

TEST(Scheduler, ProgressTime) {
  // Reset environment
  EventManager::getInstance().~EventManager();
  Scheduler::getInstance().~Scheduler();

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(2);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().progressTime(1);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().progressTime(1);

  EXPECT_EQ(count, 1);

  Scheduler::getInstance().progressTime(10);

  EXPECT_EQ(count, 1);
}