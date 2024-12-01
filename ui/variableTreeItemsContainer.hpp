#pragma once

#include <wx/treectrl.h>
#include <wx/wx.h>

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

  friend class MainWindow;
  void setModelsTree(wxTreeCtrl *modelsTree) {
    m_modelsTree = modelsTree;
    m_treeRoot = m_modelsTree->AddRoot("Simulation Models");

    wxTheApp->CallAfter( // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        [&] { m_modelsTree->Expand(m_treeRoot); });
  }

  wxTreeCtrl *m_modelsTree{};
  wxTreeItemId m_treeRoot{};
};