#pragma once

#include <string>
#include <vector>

#include "common/modelItem.hpp"

class ModelContainer {
public:
  static ModelContainer &getInstance() {
    static ModelContainer instance;
    return instance;
  }

  // TODO(renda): Improve search by doing parent.children.grandchildren type of search
  ModelItem *getModel(const std::string &modelName) {
    for (auto &model : m_models) {
      if (model->getName() == modelName) {
        return model;
      }
    }

    return nullptr;
  }

private:
  ModelContainer() = default;

  friend class Model;
  void addModel(ModelItem *model) { m_models.push_back(model); }

  std::vector<ModelItem *> m_models;
};