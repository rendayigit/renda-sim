/**
 * @file pcs.hpp
 * @author Renda Yigit
 * @brief Power Control System
 * @version 0.1
 * @date 2023-08-31
 *
 * This code was generated using ChatGPT. Find the chat link below for more information.
 * https://chatgpt.com/share/673f8749-9590-800d-9d4f-1f7a66885255
 */

#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>

#include "common/modelVariable.hpp"
#include "services/eventManager/simpleEvent.hpp"
#include "services/serviceContainer.hpp"

// Global variables for customization
constexpr double MAX_PANEL_POWER = 100.0;             // Maximum power solar panels can generate (Watts)
constexpr double BATTERY_CAPACITY = 1000.0;           // Maximum battery capacity (Watt-hours)
constexpr double BATTERY_EFFICIENCY = 0.95;           // Efficiency of the battery for charging/discharging
constexpr double PANEL_DEGRADATION_RATE = 0.99;       // Yearly degradation factor for panels
constexpr double BATTERY_DEGRADATION_RATE = 0.98;     // Yearly degradation factor for battery
constexpr double PANEL_CURRENT_VOLTAGE_RATIO = 10.0;  // Ratio of current to voltage for panels (A/V)
constexpr double BATTERY_CURRENT_VOLTAGE_RATIO = 5.0; // Ratio of current to voltage for battery (A/V)

class PowerSubsystem {
public:
  PowerSubsystem();

  void initialize();
  void step();
  void printState() const;

private:
  ModelVariable<double> m_batteryCharge;    // Current charge of the battery (Watt-hours)
  ModelVariable<double> m_powerFromPanels;  // Power drawn from solar panels (Watts)
  ModelVariable<double> m_powerFromBattery; // Power drawn from battery (Watts)
  ModelVariable<double> m_panelVoltage;     // Voltage of the solar panels (Volts)
  ModelVariable<double> m_panelCurrent;     // Current from the solar panels (Amperes)
  ModelVariable<double> m_batteryVoltage;   // Voltage of the battery (Volts)
  ModelVariable<double> m_batteryCurrent;   // Current from the battery (Amperes)
  ModelVariable<int> m_batteryAgeYears;     // Age of the battery in years
  ModelVariable<int> m_panelAgeYears;       // Age of the panels in years

  ModelVariable<double> m_sunAngle;         // Sun angle for the solar panels (radians)
  ModelVariable<double> m_powerConsumption; // Power consumption of the system (Watts)

  SimpleEvent m_powerEvent;
};
