/**
 * @file pcs.hpp
 * @author Firstname Lastname
 * @brief Power Control System
 * @version 0.1
 * @date 2023-08-31
 *
 * This code was generated using ChatGPT. Find the chat link below for more information.
 * https://chatgpt.com/share/673f8749-9590-800d-9d4f-1f7a66885255
 */

#pragma once

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>

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
  PowerSubsystem() {
    initialize(500.0, 3, 5);

    long i = 0;
    m_powerEvent.setEventFunction([&] {
      auto now = std::chrono::high_resolution_clock::now();
      auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_appStartTime).count();

      std::cout << "Power Step Time: " << std::to_string(milliseconds) << " ms" << std::endl;

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

  void initialize(double batteryInitialCharge = 500.0, int batteryAgeYears = 0, int panelAgeYears = 0) {
    m_batteryCharge = batteryInitialCharge; // Initial charge in Watt-hours
    this->m_batteryAgeYears = batteryAgeYears;
    this->m_panelAgeYears = panelAgeYears;
  }

  void step(double sunAngle, double powerConsumption) {
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
  void printState() const {
    std::cout << "Battery Charge: " << m_batteryCharge << " Wh" << std::endl;
    std::cout << "Power from Panels: " << m_powerFromPanels << " W" << std::endl;
    std::cout << "Power from Battery: " << m_powerFromBattery << " W" << std::endl;
    std::cout << "Panel Voltage: " << m_panelVoltage << " V, Panel Current: " << m_panelCurrent << " A" << std::endl;
    std::cout << "Battery Voltage: " << m_batteryVoltage << " V, Battery Current: " << m_batteryCurrent << " A"
              << std::endl;
    std::cout << "-------------------------------------" << std::endl;
  }

private:
  double m_batteryCharge{};    // Current charge of the battery (Watt-hours)
  double m_powerFromPanels{};  // Power drawn from solar panels (Watts)
  double m_powerFromBattery{}; // Power drawn from battery (Watts)
  double m_panelVoltage{};     // Voltage of the solar panels (Volts)
  double m_panelCurrent{};     // Current from the solar panels (Amperes)
  double m_batteryVoltage{};   // Voltage of the battery (Volts)
  double m_batteryCurrent{};   // Current from the battery (Amperes)
  int m_batteryAgeYears{};     // Age of the battery in years
  int m_panelAgeYears{};       // Age of the panels in years

  SimpleEvent m_powerEvent;
  std::chrono::system_clock::time_point m_appStartTime = std::chrono::high_resolution_clock::now();
};
