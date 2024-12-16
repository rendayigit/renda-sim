#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "model/model.hpp"

class ModelContainer {
public:
  static ModelContainer &getInstance() {
    static ModelContainer instance;
    return instance;
  }

  Object *getModel(const std::string &modelPath);

  nlohmann::json getModelTreeJson();

private:
  ModelContainer() = default;

  friend class Model;
  void addRootModel(Model *model) { m_models.push_back(model); }

  Object *findModel(Model *currentModel, std::stringstream &ss);

  std::vector<Model *> m_models;
};