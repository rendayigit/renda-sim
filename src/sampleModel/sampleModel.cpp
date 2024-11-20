#include <iostream>

#include "sampleModel.hpp"
#include "services/eventManager/eventManager.hpp"

constexpr double TIME_STEP = 1000; // 1 sec

SampleModel::SampleModel() : m_event(new SimpleEvent) {
  std::cout << "SampleModel Initialized" << std::endl;

  m_event->setEventFunction([&] { step(); });
  m_event->setCycleMs(TIME_STEP);
  m_event->activate();

  EventManager::getInstance().addEvent(m_event);
}

void SampleModel::step() { std::cout << "SampleModel Step" << std::endl; }
