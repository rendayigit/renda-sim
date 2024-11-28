#pragma once

#include <wx/treectrl.h>

#include "common/model.hpp"
#include "common/modelItem.hpp"

class VariableTreeItemsContainer {
public:
  static VariableTreeItemsContainer &getInstance() {
    static VariableTreeItemsContainer instance;
    return instance;
  }

  // TODO(renda): Use setModelsTree() instead by moving below logic into modelItem constructor
  void addModel(Model *model) {
    // auto model = dynamic_cast<Model *>(model->getParent());

    auto treeItem = m_modelsTree->AppendItem(m_treeRoot, model->getName());
    if (not model->getItems().empty()) {
      for (auto &item : model->getItems()) {
        m_modelsTree->AppendItem(treeItem, item->getName());
      }
    }
  }

  void addTreeItem(wxTreeItemId parentTreeItem, ModelItem *modelItem) {
    m_modelsTree->AppendItem(parentTreeItem, modelItem->getName());
  }

  // TODO(renda): Make private later
  void setModelsTree(wxTreeCtrl *modelsTree) {
    m_modelsTree = modelsTree;
    m_treeRoot = m_modelsTree->AddRoot("Models");
  }

private:
  VariableTreeItemsContainer() = default;

  wxTreeCtrl *m_modelsTree{};
  wxTreeItemId m_treeRoot{};
};