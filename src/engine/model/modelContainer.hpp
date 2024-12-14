#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "engine/model/model.hpp"

class ModelContainer {
public:
  static ModelContainer &getInstance() {
    static ModelContainer instance;
    return instance;
  }

  Object *getModel(const std::string &modelPath);

  nlohmann::json getModelTreeJson();

  // TODO(renda): Should only be called by main.cpp for subsystems
  void addModel(Model *model) { m_models.push_back(model); }

private:
  ModelContainer() = default;

  Object *findModel(Model *currentModel, std::stringstream &ss);

  std::vector<Model *> m_models;
};