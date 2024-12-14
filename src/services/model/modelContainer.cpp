#include "services/model/modelContainer.hpp"

#include <iostream>

Object *ModelContainer::getModel(const std::string &modelPath) {
  if (modelPath.empty()) {
    return nullptr;
  }

  std::stringstream ss(modelPath);
  std::string rootName;

  // Extract the root model name
  if (not std::getline(ss, rootName, '.') || rootName.empty()) {
    return nullptr; // Invalid format
  }

  // Search for the root model in m_models
  for (auto &model : m_models) {
    if (model->getName() == rootName) {
      return findModel(model, ss); // Start recursive search
    }
  }

  return nullptr; // Root model not found
}

nlohmann::json ModelContainer::getModelTreeJson() {
  nlohmann::json modelTree;

  for (auto &model : m_models) {
    modelTree.update(model->getModelTreeJson());
  }

  return modelTree;
}

Object *ModelContainer::findModel(Model *currentModel, std::stringstream &ss) {
  std::string nextName;

  // Base case: If no more names in the path, return the current object
  if (not std::getline(ss, nextName, '.')) {
    return currentModel; // The final object is found
  }

  // Search among the children of the current model
  for (auto &child : currentModel->getChildren()) {
    if (child->getName() == nextName) {
      // If there are more parts in the path, child must be a Model
      auto *childAsModel = dynamic_cast<Model *>(child);

      if (childAsModel != nullptr) {
        return findModel(childAsModel, ss); // Recursive call for the next level
      }

      // If this is the last part of the path, it must be an Object
      if (ss.rdbuf()->in_avail() == 0) { // No more tokens to parse
        return child;
      }

      // If the path continues but the child is not a Model, return nullptr
      return nullptr;
    }
  }

  return nullptr; // No child matches the current name
}
