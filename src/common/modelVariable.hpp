#pragma once

#include "common/model.hpp"
#include "common/modelItem.hpp"

template <typename t> class ModelVariable : public ModelItem {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : ModelItem(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
  }

  void setValue(t value) { m_value = value; }
  t getValue() { return m_value; }

private:
  t m_value;
};