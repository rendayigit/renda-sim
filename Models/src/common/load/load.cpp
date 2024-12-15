#include "models/common/load/load.hpp"
#include "engine/json/json.hpp"
#include "models/common/load/loadContainer.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

constexpr double ROOM_TEMPERATURE = 293.15;

Load::Load(std::string name, std::string configurationFile)
    : vbus({}), gnd({}), activeVoltageConsumption({}), activeTemperature({}), activePowerConsumption({}),
      m_name(std::move(name)), m_configurationFile(std::move(configurationFile)) {
  Json config = Json(m_configurationFile);
  m_thermalZone = config.getNode("thermalZone").getValue<std::string>();
  m_busType = m_busTypes.at(config.getNode("busType").getValue<std::string>());

  vbus.setUpdateFunction([this](double value) { updateVbusIn(value); });
  gnd.setUpdateFunction([this](double value) { updateVbusGnd(value); });

  LoadContainer::getInstance().addLoad(this);
}

Load::~Load() { LoadContainer::getInstance().removeLoad(this); }

void Load::addState(LoadState *state) {
  for (auto &stateItem : m_states) {
    if (state->getStateName() == stateItem->getStateName()) {
      throw std::invalid_argument("Tried to add an existing state.");
    }
  }

  m_states.push_back(state);
}

void Load::setActiveState(const std::string &stateName) { m_activeState = getState(stateName); }

LoadState *Load::getState(const std::string &stateName) {
  for (auto &stateItem : m_states) {
    if (stateItem->getStateName() == stateName) {
      return stateItem;
    }
  }

  throw std::invalid_argument("Tried to set an invalid state.");
}

bool Load::isVoltageInsideBounds(double value) {
  return value >= getState(ON_STATE)->getMinVoltageConsumption() and
         value <= getState(ON_STATE)->getMaxVoltageConsumption();
}

void Load::updateState(double voltage) {
  if (m_activeState == nullptr) {
    throw std::runtime_error("Active state is not set.");
  }

  if (std::isnan(voltage)) {
    voltage = 0.0;
  }

  activeVoltageConsumption.setValue(voltage);

  // TODO(renda): add rand margin between min and max values
  activePowerConsumption.setValue(m_activeState->getNominalPowerConsumption());
  // TODO(renda): add rand margin between min and max values
  activeTemperature.setValue(m_activeState->getNominalTemperature());
}

void Load::setBusType(std::string busType) {
  // Case insensitive busType set operation
  std::string busTypeName = std::move(busType);
  std::transform(busTypeName.begin(), busTypeName.end(), busTypeName.begin(), ::toupper);

  m_busType = m_busTypes.at(busTypeName);
}
