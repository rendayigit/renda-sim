#pragma once

// TODO(renda): find a better name
class VariableProperties {
public:
  bool isMonitored() const { return m_isMonitored; }

  void setIsMonitored(bool isMonitored) { m_isMonitored = isMonitored; }

private:
  bool m_isMonitored{}; // TODO(renda): Set to true if requested from client, need to be able to get the object with
                        // getPath
};