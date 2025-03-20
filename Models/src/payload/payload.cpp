#include "payload.hpp"
#include "eventManager/eventManager.hpp"
#include "logger/logger.hpp"

Payload::Payload() : Model("Payload Model", "Payload Model", nullptr), m_value("A Variable", "A Variable", this, 0.0) {
  m_event.setEventFunction([&] { step(); });
  m_event.setCycleMillis(1000);
  m_event.activate();

  EventManager::getInstance().addEvent(&m_event);

  init();
}

void Payload::init() {
  m_value.setValue(1.0);
  Logger::info("Payload Model Initialized");
}

void Payload::step() {
  // Main logic here
  m_value.setValue(m_value.getValue() + 1.0);
}
