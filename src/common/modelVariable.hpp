#pragma once

#include <string>
#include <vector>

#include "common/model.hpp"
#include "common/object.hpp"
#include "services/messaging.hpp"

template <typename t> class ModelVariable : public Object {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : Object(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
    std::cout << getPath() << std::endl; // TODO(renda): Remove after testing
  }

  void setValue(t value) {
    m_value = value;

    Messaging::getInstance().queueMessage(getPath(), std::to_string(m_value)); // TODO(renda): Remove after testing

    if (m_isMonitored) {
      Messaging::getInstance().queueMessage(getPath(), std::to_string(m_value));
    }

    if (m_isPlotted) {
      // TODO(renda): Transmit value
    }
  }

  t getValue() { return m_value; }

private:
  friend class MainWindow;

  t m_value;

  bool m_isMonitored{}; // TODO(renda): Set to true if requested from client, need to be able to get the object with
                        // getPath
  bool m_isPlotted{};
};