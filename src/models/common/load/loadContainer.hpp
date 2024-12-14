#pragma once

#include "models/common/load/load.hpp"

class LoadContainer {
public:
  static LoadContainer &getInstance() {
    static LoadContainer instance;
    return instance;
  }

  /**
   * @brief Add a load to the simulation load list
   *
   */
  void addLoad(Load *load) {
    if (load == nullptr || std::find(m_loads.begin(), m_loads.end(), load) != m_loads.end()) {
      return;
    }

    m_loads.push_back(load);
  }

  /**
   * @brief Remove a load from the simulation load list
   *
   */
  void removeLoad(Load *load) {
    if (load == nullptr) {
      return;
    }

    auto loadToBeRemoved = std::find(m_loads.begin(), m_loads.end(), load);

    if (loadToBeRemoved != m_loads.end()) {
      m_loads.erase(loadToBeRemoved);
    }
  }

  /**
   * @brief Retrieve simulation load list
   *
   * @return Simulation load list as vector
   */
  std::vector<Load *> getLoads() { return m_loads; }

  /**
   * @brief Get the load count in the given thermal zone
   *
   * @param t The thermal zone name
   *
   * @return The load count
   */
  int getThermalZoneLoadCount(const std::string &thermalZone) {
    auto loadCountInThermalZone = 0;
    for (auto &load : m_loads) {
      if (load->getThermalZone() == thermalZone) {
        loadCountInThermalZone++;
      }
    }
    return loadCountInThermalZone;
  }

private:
  LoadContainer() = default;

  std::vector<Load *> m_loads;
};
