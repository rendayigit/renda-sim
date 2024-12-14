#pragma once

#include "models/common/dataFlow.hpp"
#include "models/common/load/loadState.hpp"

#include <cfloat>
#include <map>
#include <string>

inline const std::string ON_STATE = "on_state";
inline const std::string OFF_STATE = "off_state";

inline constexpr double GND_VOLTAGE = DBL_MIN;
inline constexpr double LOAD_DEFAULT_MAX_RESISTANCE = 100E6;

// Primary : 100V , Secondary : 28V
enum class BusType { PRIMARY, SECONDARY };

class Load {
public:
  explicit Load(std::string name, std::string configurationFile);
  virtual ~Load();

  void addState(LoadState *state);
  void setActiveState(const std::string &stateName);
  void setBusType(std::string busType);
  std::string getName() { return m_name; };

  std::string getThermalZone() const { return m_thermalZone; }
  LoadState *getState(const std::string &stateName);
  LoadState *getActiveState() const { return m_activeState; }
  BusType getBusType() const { return m_busType; }
  bool isVoltageInsideBounds(double value);

  void updateState(double voltage);

  InFlow<double> vbus;
  InFlow<double> gnd;

  OutFlow<double> activeVoltageConsumption; /* Volts    Active Voltage */
  OutFlow<double> activeTemperature;        /* K    Active Temperature */
  OutFlow<double> activePowerConsumption;   /* Watts    Active Power */

protected:
  virtual void updateVbusIn(double value) = 0;
  virtual void updateVbusGnd(double value) = 0;

private:
  std::string m_name;
  std::string m_configurationFile;

  std::string m_thermalZone;

  LoadState *m_activeState{};
  std::vector<LoadState *> m_states;

  std::map<std::string, BusType> m_busTypes = {{"PRIMARY", BusType::PRIMARY}, {"SECONDARY", BusType::SECONDARY}};
  BusType m_busType;
};