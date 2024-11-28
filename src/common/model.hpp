#pragma once

#include <utility>
#include <vector>

#include "common/modelItem.hpp"

class Model : public ModelItem {
public:
  explicit Model(std::string name, std::string description, ModelItem *parent)
      : ModelItem(std::move(name), std::move(description), parent) {}

  std::vector<ModelItem *> getItems() const { return m_items; }

  // TODO(renda): Make only accessible by ModelVariable
  void addChild(ModelItem *child) { m_items.push_back(child); }

private:
  std::vector<ModelItem *> m_items;
};