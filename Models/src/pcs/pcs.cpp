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
#include "eventManager.hpp"
#include "logger.hpp"
#include "model.hpp"

PowerSubsystem::PowerSubsystem()
    : Model("Power Control Subsystem", "Power Control Subsystem", nullptr),
      m_batteryCharge("Battery Charge", "Current charge of the battery (Watt-hours)", this, 500.0),
      m_powerFromPanels("Power From Panels", "Power drawn from solar panels (Watts)", this, {}),
      m_powerFromBattery("Power From Battery", "Power drawn from battery (Watts)", this, {}),
      m_panelVoltage("Panel Voltage", "Voltage of the solar panels (Volts)", this, {}),
      m_panelCurrent("Panel Current", "Current from the solar panels (Amperes)", this, {}),
      m_batteryVoltage("Battery Voltage", "Voltage of the battery (Volts)", this, {}),
      m_batteryCurrent("Battery Current", "Current from the battery (Amperes)", this, {}),
      m_batteryAgeYears("Battery Age Years", "Age of the battery in years", this, 3),
      m_panelAgeYears("Panel Age Years", "Age of the panels in years", this, 5),
      m_sunAngle("Sun Angle", "Sun angle for the solar panels (radians)", this, {}),
      m_powerConsumption("Power Consumption", "Power consumption of the system (Watts)", this, {}) {

  initialize();

  m_powerEvent.setEventFunction([&] { step(); });
  m_powerEvent.setCycleMillis(100);
  m_powerEvent.activate();
  EventManager::getInstance().addEvent(&m_powerEvent);
}

void PowerSubsystem::initialize() {
  // TODO(renda): Initialize the power subsystem here
  // Read initial values from JSON

  Logger::info("Power Subsystem Initialized");
}

void PowerSubsystem::step() {
  // TODO(renda): Get sun angle from aocs and power consumption from loads
  static long i = 0;
  m_sunAngle.setValue((M_PI / 4.0) * (std::sin(i * 0.1) + 1.0)); // Simulated sun angle
  m_powerConsumption.setValue(50.0 + 10.0 * std::cos(i * 0.2));  // Simulated power consumption
  i++;

  // Degraded panel efficiency due to age
  double panelEfficiency = std::pow(PANEL_DEGRADATION_RATE, m_panelAgeYears.getValue());
  double panelPower = MAX_PANEL_POWER * std::max(std::cos(m_sunAngle.getValue()), 0.0) * panelEfficiency;

  // Battery degradation due to age and temperature (simplified model)
  double batteryEffectiveCapacity = BATTERY_CAPACITY * std::pow(BATTERY_DEGRADATION_RATE, m_batteryAgeYears.getValue());

  // Power distribution logic
  if (panelPower >= m_powerConsumption.getValue()) {
    // Panels provide all power; excess charges the battery
    m_powerFromPanels.setValue(m_powerConsumption.getValue());
    m_powerFromBattery.setValue(0.0);

    double excessPower = panelPower - m_powerConsumption.getValue();
    m_batteryCharge.setValue(m_batteryCharge.getValue() +
                             excessPower * BATTERY_EFFICIENCY * 0.1 / 3600.0); // Charging in Watt-hours
  } else {
    // Panels and battery together provide power
    m_powerFromPanels.setValue(panelPower);
    m_powerFromBattery.setValue(m_powerConsumption.getValue() - panelPower);

    m_batteryCharge.setValue(m_batteryCharge.getValue() - m_powerFromBattery.getValue() / BATTERY_EFFICIENCY * 0.1 /
                                                              3600.0); // Discharging in Watt-hours
  }

  // Clamp battery charge to its effective capacity
  m_batteryCharge.setValue(std::clamp(m_batteryCharge.getValue(), 0.0, batteryEffectiveCapacity));

  // Calculate currents and voltages
  m_panelVoltage.setValue(std::sqrt(panelPower / PANEL_CURRENT_VOLTAGE_RATIO));
  m_panelCurrent.setValue(panelPower / m_panelVoltage.getValue());

  m_batteryVoltage.setValue(std::sqrt(m_batteryCharge.getValue() / BATTERY_CURRENT_VOLTAGE_RATIO));
  m_batteryCurrent.setValue(m_powerFromBattery.getValue() / m_batteryVoltage.getValue());
}
