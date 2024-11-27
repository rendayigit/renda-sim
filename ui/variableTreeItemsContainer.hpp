#pragma once

#include <wx/treectrl.h>

#include "common/modelItem.hpp"

class VariableTreeItemsContainer {
public:
  static VariableTreeItemsContainer &getInstance() {
    static VariableTreeItemsContainer instance;
    return instance;
  }

  void addVariable(ModelItem *item) { m_modelsTree->AppendItem(m_treeRoot, item->getName()); }

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