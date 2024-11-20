#include <iostream>

#include "sampleModel.hpp"

constexpr double TIME_STEP = 0.1;

SampleModel::SampleModel() : m_event(new ModelEvent) {
  std::cout << "SampleModel Initialized" << std::endl;

  m_event->setEventFunction([&] { step(); });
  m_event->setCycleTime(TIME_STEP);
  m_event->activate();
}

void SampleModel::step() { std::cout << "SampleModel Step" << std::endl; }
