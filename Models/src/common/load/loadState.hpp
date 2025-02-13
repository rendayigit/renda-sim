#pragma once

#include <string>

class LoadState {
public:
  LoadState(std::string configurationFile, std::string stateName);

  /**
   * Sets the temperature parameters of a Load State. It makes sure that the logic is valid. That is
   * (min<=nom<=max).
   * @param nominal Nominal temperature [W]
   * @param max Maximum temperature [W]
   * @param min Minimum temperature [W]
   */
  void setTemperatureParameters(double nominal, double max, double min);

  /**
   * Sets the voltage parameters of a Load State. It makes sure that the logic is valid. That is
   * (min<=nom<=max).
   * @param nominal Nominal voltage [V]
   * @param max Maximum voltage [V]
   * @param min Minimum voltage [V]
   */
  void setVoltageParameters(double nominal, double max, double min);

  /**
   * Sets the power consumption parameters of a Load State. It makes sure that the logic is valid. That is
   * (min<=nom<=max).
   * @param nominal Nominal power [W]
   * @param max Maximum power [W]
   * @param min Minimum power [W]
   */
  void setPowerParameters(double nominal, double max, double min);

  double getNominalVoltageConsumption() const { return m_nominalVoltageConsumption; }
  double getMaxVoltageConsumption() const { return m_maxVoltageConsumption; }
  double getMinVoltageConsumption() const { return m_minVoltageConsumption; }

  double getNominalTemperature() const { return m_nominalTemperature; }
  double getMaxTemperature() const { return m_maxTemperature; }
  double getMinTemperature() const { return m_minTemperature; }

  double getNominalPowerConsumption() const { return m_nominalPowerConsumption; }
  double getMaxPowerConsumption() const { return m_maxPowerConsumption; }
  double getMinPowerConsumption() const { return m_minPowerConsumption; }

  std::string getStateName() const { return m_stateName; }

private:
  std::string m_configurationFile;
  std::string m_stateName;

  double m_nominalVoltageConsumption{}; /* V    Nominal Voltage Consumption */
  double m_maxVoltageConsumption{};     /* V    Max Voltage Consumption */
  double m_minVoltageConsumption{};     /* V    Min Voltage Consumption */

  double m_nominalTemperature{}; /* K    Nominal Temperature */
  double m_maxTemperature{};     /* K    Max Temperature */
  double m_minTemperature{};     /* K    Min Temperature */

  double m_nominalPowerConsumption{}; /* W    Nominal Power Consumption */
  double m_maxPowerConsumption{};     /* W    Max Power Consumption */
  double m_minPowerConsumption{};     /* W    Min Power Consumption */
};