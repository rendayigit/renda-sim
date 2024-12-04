#pragma once

#include <utility>
#include <vector>

#include "common/modelItem.hpp"
#include "services/modelContainer.hpp"

class Model : public ModelItem {
public:
  explicit Model(std::string name, std::string description, ModelItem *parent)
      : ModelItem(std::move(name), std::move(description), parent) {
    ModelContainer::getInstance().addModel(this); // TODO(renda): maybe move to ModelItem Constructor
    // TODO(renda): Add model to model tree
  }

  std::vector<ModelItem *> getItems() const { return m_items; }

private:
  template <typename t> friend class ModelVariable;
  void addChild(ModelItem *child) {
    m_items.push_back(child);
    ModelContainer::getInstance().addModel(child); // TODO(renda): maybe move to ModelItem Constructor
    // TODO(renda): Add child model to model tree
  }

  std::vector<ModelItem *> m_items;
};