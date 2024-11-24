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

PowerSubsystem::PowerSubsystem() {
  initialize(500.0, 3, 5);

  long i = 0;
  m_powerEvent.setEventFunction([&] {
    std::cout << "Power Step Real Millis: " << std::to_string(Timer::getInstance().currentMillis()) << std::endl;

    double sunAngle = (M_PI / 4.0) * (std::sin(i * 0.1) + 1.0); // Simulated sun angle
    double powerConsumption = 50.0 + 10.0 * std::cos(i * 0.2);  // Simulated power consumption

    std::cout << "Sun Angle: " << sunAngle << std::endl;
    std::cout << "Power Needed: " << powerConsumption << " W" << std::endl;

    step(sunAngle, powerConsumption);
    i++;
  });

  m_powerEvent.setCycleMillis(100);
  m_powerEvent.activate();
  ServiceContainer::getInstance().eventManager()->addEvent(&m_powerEvent);
}

void PowerSubsystem::initialize(double batteryInitialCharge, int batteryAgeYears, int panelAgeYears) {
  m_batteryCharge = batteryInitialCharge; // Initial charge in Watt-hours
  this->m_batteryAgeYears = batteryAgeYears;
  this->m_panelAgeYears = panelAgeYears;
}

void PowerSubsystem::step(double sunAngle, double powerConsumption) {
  // Degraded panel efficiency due to age
  double panelEfficiency = std::pow(PANEL_DEGRADATION_RATE, m_panelAgeYears);
  double panelPower = MAX_PANEL_POWER * std::max(std::cos(sunAngle), 0.0) * panelEfficiency;

  // Battery degradation due to age and temperature (simplified model)
  double batteryEffectiveCapacity = BATTERY_CAPACITY * std::pow(BATTERY_DEGRADATION_RATE, m_batteryAgeYears);

  // Power distribution logic
  if (panelPower >= powerConsumption) {
    // Panels provide all power; excess charges the battery
    m_powerFromPanels = powerConsumption;
    m_powerFromBattery = 0.0;

    double excessPower = panelPower - powerConsumption;
    m_batteryCharge += excessPower * BATTERY_EFFICIENCY * 0.1 / 3600.0; // Charging in Watt-hours
  } else {
    // Panels and battery together provide power
    m_powerFromPanels = panelPower;
    m_powerFromBattery = powerConsumption - panelPower;

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
  std::cout << "Battery Charge: " << m_batteryCharge << " Wh" << std::endl;
  std::cout << "Power from Panels: " << m_powerFromPanels << " W" << std::endl;
  std::cout << "Power from Battery: " << m_powerFromBattery << " W" << std::endl;
  std::cout << "Panel Voltage: " << m_panelVoltage << " V, Panel Current: " << m_panelCurrent << " A" << std::endl;
  std::cout << "Battery Voltage: " << m_batteryVoltage << " V, Battery Current: " << m_batteryCurrent << " A"
            << std::endl;
  std::cout << "-------------------------------------" << std::endl;
}
