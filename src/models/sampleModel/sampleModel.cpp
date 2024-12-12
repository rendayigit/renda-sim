#include <iostream>
#include <string>

#include "sampleModel.hpp"
#include "services/serviceContainer.hpp"
#include "services/timer/timer.hpp"
#include <spdlog/spdlog.h>

constexpr double TIME_STEP_1_SEC = 1000;
constexpr double TIME_STEP_500_MSEC = 500;
constexpr double TIME_STEP_100_MSEC = 100;
constexpr double TIME_STEP_1_MSEC = 1;

SampleModel::SampleModel()
    : Model("Sample Model", "Sample Model", nullptr), m_eventSlow(new SimpleEvent), m_eventFast(new SimpleEvent),
      m_eventFaster(new SimpleEvent), m_eventFastest(new SimpleEvent),
      m_doubleValue("Double Variable", "Sample Double Variable", this, 123.4),
      m_integerValue("Integer Variable", "Sample Integer Variable", this, -1),
      m_booleanValue("Boolean Variable", "Sample Boolean Variable", this, true),
      m_stringValue("String Variable", "Sample String Variable", this, "ABCD") {
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

  std::cout << "Sample Model Initialized" << std::endl;

  m_logger = spdlog::daily_logger_mt("ENGINE", "Engine.log", 0, 0);
  m_logger->set_pattern("[%H:%M:%S.%f %z] [%n] [%l] [thread %t] %v");
}

void SampleModel::step(int stepTime) {
  m_logger->info(std::to_string(stepTime) +
                 " ms Step, Real Millis: " + std::to_string(Timer::getInstance().simMillis()));

  if (stepTime == TIME_STEP_1_SEC) {
    m_integerValue.setValue(m_integerValue.getValue() + 1);
  }
}
