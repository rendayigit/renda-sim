#pragma once

#include <vector>

#include "common/model.hpp"
#include "common/modelItem.hpp"

template <typename t> class ModelVariable : public ModelItem {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : ModelItem(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
  }

  void setValue(t value) {
    m_value = value;

    if (m_isMonitored) {
      // TODO(renda): Transmit value
    }

    if (m_isPlotted) {
      // TODO(renda): Transmit value
    }
  }

  t getValue() { return m_value; }

private:
  friend class MainWindow;

  t m_value;

  bool m_isMonitored{};
  bool m_isPlotted{};
};