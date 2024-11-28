#pragma once

#include <wx/treectrl.h>

#include "common/modelItem.hpp"

class VariableTreeItemsContainer {
public:
  static VariableTreeItemsContainer &getInstance() {
    static VariableTreeItemsContainer instance;
    return instance;
  }

  wxTreeItemId addTreeItem(wxTreeItemId parentTreeItem, ModelItem *modelItem) {
    if (parentTreeItem == nullptr) {
      return m_modelsTree->AppendItem(m_treeRoot, modelItem->getName());
    }

    return m_modelsTree->AppendItem(parentTreeItem, modelItem->getName());
  }

private:
  VariableTreeItemsContainer() = default;

  friend class MyFrame;
  void setModelsTree(wxTreeCtrl *modelsTree) {
    m_modelsTree = modelsTree;
    m_treeRoot = m_modelsTree->AddRoot("Models");
  }

  wxTreeCtrl *m_modelsTree{};
  wxTreeItemId m_treeRoot{};
};