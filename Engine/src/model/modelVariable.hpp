#pragma once

#include <iostream>
#include <string>

#include "messaging/messaging.hpp"
#include "model/model.hpp"
#include "model/object.hpp"
#include "model/variableProperties.hpp"

template <typename t> class ModelVariable : public Object, public VariableProperties {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : Object(name, description, parent), m_value(initialValue) {
    if (parent != nullptr) {
      parent->addChild(this);
    } else {
      // TODO(renda): Log a better way
      std::cerr << "Variable " + name + " has no parent assigned" << std::endl;
    }
  }

  void setValue(t value) {
    m_value = value;

    if (isMonitored()) {
      Messaging::getInstance().queueMessage(getPath(), std::to_string(m_value));
    }
  }

  t getValue() { return m_value; }

private:
  friend class MainWindow;

  t m_value;
};