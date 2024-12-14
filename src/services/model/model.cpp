#include "services/model/model.hpp"

Model::Model(std::string name, std::string description, Object *parent)
    : Object(std::move(name), std::move(description), parent) {
  auto *parentModel = dynamic_cast<Model *>(parent);
  if (parentModel != nullptr) {
    parentModel->addChild(this);
  }
}

void Model::addChild(Object *child) { m_children.push_back(child); }

nlohmann::json Model::getModelTreeJson() {
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

