#include <iostream>
#include <string>

#include "sampleModel.hpp"
#include "services/serviceContainer.hpp"
#include "services/timer/timer.hpp"

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

  ServiceContainer::getInstance().eventManager()->addEvent(m_eventSlow);
  ServiceContainer::getInstance().eventManager()->addEvent(m_eventFast);
  ServiceContainer::getInstance().eventManager()->addEvent(m_eventFaster);
  ServiceContainer::getInstance().eventManager()->addEvent(m_eventFastest);
}

void SampleModel::step(int stepTime) {
  m_logger.log(LogLevel::LOG_INFO,
               std::to_string(stepTime) + " ms Step, Real Millis: " + std::to_string(Timer::getInstance().simMillis()));

  // std::cout << std::to_string(stepTime) + " ms Step, Real Millis: " +
  // std::to_string(Timer::getInstance().simMillis())
  //           << std::endl;
}
