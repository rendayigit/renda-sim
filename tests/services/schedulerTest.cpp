#include <gtest/gtest.h>
#include <thread>

#include "services/eventManager/eventManager.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/scheduler/scheduler.hpp"

TEST(Scheduler, StartStop) {
  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(0);
  evt.activate();
  eventManager.addEvent(&evt);

  EXPECT_EQ(count, 0);

  scheduler.start();

  std::this_thread::sleep_for(std::chrono::seconds(1));

  scheduler.stop();

  int currentCount = count;

  EXPECT_GT(currentCount, 0);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  EXPECT_EQ(currentCount, count);
}

TEST(Scheduler, ProgressTime) {
  EventManager eventManager;
  Scheduler scheduler(&eventManager);

  int count = 0;
  SimpleEvent evt;
  evt.setEventFunction([&] { count += 1; });
  evt.setNextMillis(2);
  evt.activate();
  eventManager.addEvent(&evt);

  EXPECT_EQ(count, 0);

  scheduler.progressTime(1);

  EXPECT_EQ(count, 0);

  scheduler.progressTime(1);

  EXPECT_EQ(count, 1);

  scheduler.progressTime(10);

  EXPECT_EQ(count, 1);
}