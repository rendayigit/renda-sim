#pragma once

#include <utility>
#include <vector>

#include "common/modelItem.hpp"

class Model : public ModelItem {
public:
  explicit Model(std::string name, std::string description, ModelItem *parent)
      : ModelItem(std::move(name), std::move(description), parent) {}

  std::vector<ModelItem *> getItems() const { return m_items; }

private:
  template <typename t> friend class ModelVariable;
  void addChild(ModelItem *child) { m_items.push_back(child); }

  std::vector<ModelItem *> m_items;
};