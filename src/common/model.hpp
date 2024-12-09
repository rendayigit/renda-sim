#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "common/object.hpp"

class Model : public Object {
public:
  explicit Model(std::string name, std::string description, Object *parent)
      : Object(std::move(name), std::move(description), parent) {
    auto *parentModel = dynamic_cast<Model *>(parent);
    if (parentModel != nullptr) {
      parentModel->addChild(this);
    }
  }

  std::vector<Object *> getItems() const { return m_children; }

  nlohmann::json getModelTreeJson() {
    nlohmann::json modelTree;

    for (auto &child : m_children) {
      auto *model = dynamic_cast<Model *>(child);
      if (model != nullptr) {
        modelTree[getName()].push_back(model->getModelTreeJson());
      } else {
        modelTree[getName()].push_back(child->getName());
      }
    }

    return modelTree;
  }

private:
  template <typename t> friend class ModelVariable;

  void addChild(Object *child) { m_children.push_back(child); }

  std::vector<Object *> m_children;
};