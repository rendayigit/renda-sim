#include "loadState.hpp"

#include "services/json/json.hpp"

#include <cmath>

LoadState::LoadState(std::string configurationFile, std::string stateName)
    : m_configurationFile(std::move(configurationFile)), m_stateName(std::move(stateName)) {

  setVoltageParameters(
      Json(m_configurationFile).getNode(m_stateName).getNode("nominalVoltageConsumption").getValue<double>(),
      Json(m_configurationFile).getNode(m_stateName).getNode("maxVoltageConsumption").getValue<double>(),
      Json(m_configurationFile).getNode(m_stateName).getNode("minVoltageConsumption").getValue<double>());

  setTemperatureParameters(
      Json(m_configurationFile).getNode(m_stateName).getNode("nominalTemperature").getValue<double>(),
      Json(m_configurationFile).getNode(m_stateName).getNode("maxTemperature").getValue<double>(),
      Json(m_configurationFile).getNode(m_stateName).getNode("minTemperature").getValue<double>());

  setPowerParameters(Json(m_configurationFile).getNode(m_stateName).getNode("nominalPower").getValue<double>(),
                     Json(m_configurationFile).getNode(m_stateName).getNode("maxPower").getValue<double>(),
                     Json(m_configurationFile).getNode(m_stateName).getNode("minPower").getValue<double>());
}

void LoadState::setTemperatureParameters(double nominal, double max, double min) {
  if ((max < 0) or (min < 0) or (nominal < 0)) {
    throw std::invalid_argument("Tried to set a Kelvin Temperature Value that is less than 0.");
  }

  if ((max >= nominal) && (nominal >= min)) {
    m_minTemperature = min;
    m_maxTemperature = max;
    m_nominalTemperature = nominal;
  } else {
    throw std::invalid_argument("Tried to set an invalid set of Temperature Values.");
  }
}

void LoadState::setVoltageParameters(double nominal, double max, double min) {
  // All voltages that are defined for a specific Load, must be defined POSITIVE.
  // Check Zero Consistency
  if ((nominal >= 0) && (max >= 0) && (min >= 0)) {
    // Check Logic Consistency
    if ((max >= nominal) && (nominal >= min)) {
      m_minVoltageConsumption = min;
      m_maxVoltageConsumption = max;
      m_nominalVoltageConsumption = nominal;
    } else {
      throw std::invalid_argument("Tried to set an invalid set of voltage Values.");
    }
  } else {
    throw std::invalid_argument("Tried to set an negative voltage Value.");
  }
}

void LoadState::setPowerParameters(double nominal, double max, double min) {
  if ((max >= nominal) && (nominal >= min)) {
    m_minPowerConsumption = min;
    m_maxPowerConsumption = max;
    m_nominalPowerConsumption = nominal;
  } else {
    throw std::invalid_argument("Tried to set an invalid set of Power Values.");
  }
}