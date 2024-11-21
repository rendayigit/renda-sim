#include <iostream>

#include "sampleModel.hpp"
#include "services/eventManager/eventManager.hpp"

constexpr double TIME_STEP_1_SEC = 1000;
constexpr double TIME_STEP_500_MSEC = 500;
constexpr double TIME_STEP_100_MSEC = 100;
constexpr double TIME_STEP_1_MSEC = 1;

SampleModel::SampleModel()
    : m_eventSlow(new SimpleEvent), m_eventFast(new SimpleEvent), m_eventFaster(new SimpleEvent),
      m_eventFastest(new SimpleEvent) {
  std::cout << "SampleModel Initialized" << std::endl;

  m_eventSlow->setEventFunction([&] { step(1000); });
  m_eventSlow->setCycleMillis(TIME_STEP_1_SEC);
  m_eventSlow->activate();

  m_eventFast->setEventFunction([&] { step(500); });
  m_eventFast->setCycleMillis(TIME_STEP_500_MSEC);
  m_eventFast->activate();

  m_eventFaster->setEventFunction([&] { step(100); });
  m_eventFaster->setCycleMillis(TIME_STEP_100_MSEC);
  m_eventFaster->activate();

  m_eventFastest->setEventFunction([&] { step(1); });
  m_eventFastest->setCycleMillis(TIME_STEP_1_MSEC);
  m_eventFastest->activate();

  EventManager::getInstance().addEvent(m_eventSlow);
  EventManager::getInstance().addEvent(m_eventFast);
  EventManager::getInstance().addEvent(m_eventFaster);
  EventManager::getInstance().addEvent(m_eventFastest);
}

void SampleModel::step(int stepTime) {
  auto now = std::chrono::steady_clock::now();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_appStartTime).count();

  std::cout << stepTime << " ms Step " << std::to_string(milliseconds) << std::endl;
}
