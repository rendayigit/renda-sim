#include "sampleModel/sampleModel.hpp"
#include "eventManager/eventManager.hpp"
#include "logger/logger.hpp"
#include <vector>

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
      m_stringValue("String Variable", "Sample String Variable", this, "ABCD"),
      m_uintValue("Uint", "Sample Uint", this, 15) {

  std::vector<int> myVect;
  myVect.push_back(1);
  myVect.push_back(3);
  myVect.push_back(5);

  // ModelVariable<std::vector<int>> modelVarVector("m_modelVarVector", "m_modelVarVector", this, myVect);
  m_modelVarVector = new ModelVariable<std::vector<int>>("m_modelVarVector", "m_modelVarVector", this, myVect);

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

  m_arrayValue.push_back(new ModelVariable<int>("Array Variable[0]", "Sample Array Variable 0", this, -1));
  m_arrayValue.push_back(new ModelVariable<int>("Array Variable[1]", "Sample Array Variable 1", this, -1));
  m_arrayValue.push_back(new ModelVariable<int>("Array Variable[2]", "Sample Array Variable 2", this, -1));
  m_arrayValue.push_back(new ModelVariable<int>("Array Variable[3]", "Sample Array Variable 3", this, -1));

  // FIXME(renda): Why does this not work?
  // m_arrayValue.emplace_back("Array Variable[0]", "Sample Array Variable 0", this, -1);
  // m_arrayValue.emplace_back("Array Variable[1]", "Sample Array Variable 1", this, -1);
  // m_arrayValue.emplace_back("Array Variable[2]", "Sample Array Variable 2", this, -1);
  // m_arrayValue.emplace_back("Array Variable[3]", "Sample Array Variable 3", this, -1);

  // FIXME(renda): Variable display cannot view this because uint is not defined in messageparser, add all primitive
  // types to messageparser
  m_uintValue.setValue(15);

  Logger::info("Sample Model Initialized");
}

void SampleModel::step(int stepTime) {
  // TODO(renda): Do something about below code
  // Logger::info(std::to_string(stepTime) +
  //                     " ms Step, Real Millis: " + std::to_string(Timer::getInstance().simMillis()));

  if (stepTime == TIME_STEP_1_SEC) {
    m_integerValue.setValue(m_integerValue.getValue() + 1);
    m_arrayValue.at(0)->setValue(m_integerValue.getValue());
    m_arrayValue.at(1)->setValue(m_integerValue.getValue() * 2);
    m_arrayValue.at(2)->setValue(m_integerValue.getValue() * 3);
    m_arrayValue.at(3)->setValue(m_integerValue.getValue() * 4);

    std::vector<int> a = m_modelVarVector->getValue();
    a.at(0) += 1;
    m_modelVarVector->setValue(a);
  }
}
