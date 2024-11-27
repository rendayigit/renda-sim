#pragma once

#include "common/modelItem.hpp"
#include "ui/variableTreeItemsContainer.hpp"

template <typename t> class ModelVariable : public ModelItem {
public:
  explicit ModelVariable(std::string name, std::string description, t initialValue)
      : ModelItem(name, description), m_value(initialValue) {
    VariableTreeItemsContainer::getInstance().addVariable(this);
  }

  void setValue(t value) { m_value = value; }
  t getValue() { return m_value; }

private:
  t m_value;
};