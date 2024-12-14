#pragma once

#include <string>
#include <vector>

#include "engine/messaging/messaging.hpp"
#include "engine/model/model.hpp"
#include "engine/model/object.hpp"
#include "engine/model/variableProperties.hpp"

template <typename t> class ModelVariable : public Object, public VariableProperties {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : Object(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
  }

  void setValue(t value) {
    m_value = value;

    if (isMonitored()) {
      Messaging::getInstance().queueMessage(getPath(), std::to_string(m_value));
    }

    if (isPlotted()) {
      // TODO(renda): Transmit value
    }
  }

  t getValue() { return m_value; }

private:
  friend class MainWindow;

  t m_value;
};