#include <chrono>
#include <gtest/gtest.h>
#include <thread>

#include "eventManager/eventManager.hpp"
#include "eventManager/simpleEvent.hpp"
#include "scheduler/scheduler.hpp"

TEST(Scheduler, StartStop) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(0);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().start();

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  Scheduler::getInstance().stop();

  int currentCount = count;

  EXPECT_GT(currentCount, 0);

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  EXPECT_EQ(currentCount, count);
}

TEST(Scheduler, runFor) {
  // Reset environment
  EventManager::getInstance().clearEvents();
  Scheduler::getInstance().reset();

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(20);
  evt.activate();
  EventManager::getInstance().addEvent(&evt);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().progressSim(10);

  EXPECT_EQ(count, 0);

  Scheduler::getInstance().progressSim(10);

  EXPECT_EQ(count, 1);

  Scheduler::getInstance().progressSim(100);

  EXPECT_EQ(count, 1);
}