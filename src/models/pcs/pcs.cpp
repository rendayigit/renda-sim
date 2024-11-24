/**
 * @file pcs.cpp
 * @author Renda Yigit
 * @brief Power Control System
 * @version 0.1
 * @date 2023-08-31
 *
 * This code was generated using ChatGPT. Find the chat link below for more information.
 * https://chatgpt.com/share/673f8749-9590-800d-9d4f-1f7a66885255
 */

#include "pcs/pcs.hpp"
#include "services/timer/timer.hpp"

PowerSubsystem::PowerSubsystem()
    : m_batteryCharge(500.0) /* Initial charge in Watt-hours */, m_batteryAgeYears(3), m_panelAgeYears(5) {

  initialize();

  m_powerEvent.setEventFunction([&] { step(); });
  m_powerEvent.setCycleMillis(100);
  m_powerEvent.activate();
  ServiceContainer::getInstance().eventManager()->addEvent(&m_powerEvent);
}

void PowerSubsystem::initialize() {
  // TODO(renda): Initialize the power subsystem here
  // Read initial values from JSON
}

void PowerSubsystem::step() {
  // TODO(renda): Get sun angle from aocs and power consumption from loads
  static long i = 0;
  m_sunAngle = (M_PI / 4.0) * (std::sin(i * 0.1) + 1.0); // Simulated sun angle
  m_powerConsumption = 50.0 + 10.0 * std::cos(i * 0.2);  // Simulated power consumption
  i++;

  // Degraded panel efficiency due to age
  double panelEfficiency = std::pow(PANEL_DEGRADATION_RATE, m_panelAgeYears);
  double panelPower = MAX_PANEL_POWER * std::max(std::cos(m_sunAngle), 0.0) * panelEfficiency;

  // Battery degradation due to age and temperature (simplified model)
  double batteryEffectiveCapacity = BATTERY_CAPACITY * std::pow(BATTERY_DEGRADATION_RATE, m_batteryAgeYears);

  // Power distribution logic
  if (panelPower >= m_powerConsumption) {
    // Panels provide all power; excess charges the battery
    m_powerFromPanels = m_powerConsumption;
    m_powerFromBattery = 0.0;

    double excessPower = panelPower - m_powerConsumption;
    m_batteryCharge += excessPower * BATTERY_EFFICIENCY * 0.1 / 3600.0; // Charging in Watt-hours
  } else {
    // Panels and battery together provide power
    m_powerFromPanels = panelPower;
    m_powerFromBattery = m_powerConsumption - panelPower;

    m_batteryCharge -= m_powerFromBattery / BATTERY_EFFICIENCY * 0.1 / 3600.0; // Discharging in Watt-hours
  }

  // Clamp battery charge to its effective capacity
  m_batteryCharge = std::clamp(m_batteryCharge, 0.0, batteryEffectiveCapacity);

  // Calculate currents and voltages
  m_panelVoltage = std::sqrt(panelPower / PANEL_CURRENT_VOLTAGE_RATIO);
  m_panelCurrent = panelPower / m_panelVoltage;

  m_batteryVoltage = std::sqrt(m_batteryCharge / BATTERY_CURRENT_VOLTAGE_RATIO);
  m_batteryCurrent = m_powerFromBattery / m_batteryVoltage;

  // Print state for debugging
  printState();
}

// Debug: Print the current state of the power subsystem
void PowerSubsystem::printState() const {
  if (logMessage == nullptr) {
    return;
  }

  logMessage("PowerSubsystem State:\n");
  logMessage("Power Step Real Millis: " + std::to_string(Timer::getInstance().currentMillis()) + "\n");
  logMessage("Sun Angle: " + std::to_string(m_sunAngle) + "\n");
  logMessage("Power Needed: " + std::to_string(m_powerConsumption) + " W\n");
  logMessage("Battery Charge: " + std::to_string(m_batteryCharge) + " Wh\n");
  logMessage("Power from Panels: " + std::to_string(m_powerFromPanels) + " W\n");
  logMessage("Power from Battery: " + std::to_string(m_powerFromBattery) + " W\n");
  logMessage("Panel Voltage: " + std::to_string(m_panelVoltage) +
             " V, Panel Current: " + std::to_string(m_panelCurrent) + " A\n");
  logMessage("Battery Voltage: " + std::to_string(m_batteryVoltage) +
             " V, Battery Current: " + std::to_string(m_batteryCurrent) + " A\n");
  logMessage("-------------------------------------\n");
}
