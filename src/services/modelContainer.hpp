#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "common/model.hpp"

class ModelContainer {
public:
  static ModelContainer &getInstance() {
    static ModelContainer instance;
    return instance;
  }

  // TODO(renda): Improve search by doing parent.children.grandchildren type of search
  Object *getModel(const std::string &modelName) {
    for (auto &model : m_models) {
      if (model->getName() == modelName) {
        return model;
      }
    }

    return nullptr;
  }

  nlohmann::json getModelTreeJson() {
    nlohmann::json modelTree;

    for (auto &model : m_models) {
      modelTree.update(model->getModelTreeJson());
    }

    return modelTree;
  }

  // TODO(renda): Should only be called by main.cpp for subsystems
  void addModel(Model *model) { m_models.push_back(model); }

private:
  ModelContainer() = default;
  std::vector<Model *> m_models;
};