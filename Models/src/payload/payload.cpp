#include "payload.hpp"
#include "eventManager/eventManager.hpp"
#include "logger/logger.hpp"

Payload::Payload()
    : Model("Payload Model", "Payload Model", nullptr),
      // CSU
      m_csuPower("CSU Power A", "CSU Power A", this, 0.0), m_dcu1Power("DCU1 Power", "DCU1 Power", this, 0.0),
      m_dcu2Power("DCU2 Power", "DCU2 Power", this, 0.0), m_afsCuPower("AFS CU Power", "AFS CU Power", this, 0.0),
      // HCU
      m_tmd1A("HCU TMD 1 A", "HCU TMD 1 A", this, {}), m_tmd1B("HCU TMD 1 B", "HCU TMD 1 B", this, {}),
      m_spp1A("HCU SPP 1 A", "HCU SPP 1 A", this, {}), m_spp1B("HCU SPP 1 B", "HCU SPP 1 B", this, {}),
      m_upp1A("HCU UPP 1 A", "HCU UPP 1 A", this, {}), m_upp1B("HCU UPP 1 B", "HCU UPP 1 B", this, {}) {
  m_event.setEventFunction([&] { step(); });
  m_event.setCycleMillis(1000);
  m_event.activate();

  EventManager::getInstance().addEvent(&m_event);

  init();
}

void Payload::init() {
  m_csuPower.setValue(13.0);

  DataStruct data;
  data.boolean = false;
  m_tmd1A.setValue(data);

  Logger::info("Payload Model Initialized");
}

void Payload::step() {
  // Main logic here
  m_csuPower.setValue(m_csuPower.getValue() + 1.0);
}
