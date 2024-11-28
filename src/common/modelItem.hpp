#pragma once

#include <string>
#include <utility>
// #include <wx/treectrl.h>

// #include "ui/variableTreeItemsContainer.hpp"

// TODO(renda): Review commented code

class ModelItem {
public:
  explicit ModelItem(std::string name, std::string description, ModelItem *parent)
      : m_name(std::move(name)), m_description(std::move(description)), m_parent(parent) {

    // VariableTreeItemsContainer::getInstance().addModel(this);
  }

  std::string getName() const { return m_name; }
  std::string getDescription() const { return m_description; }

  ModelItem *getParent() const { return m_parent; }

private:
  std::string m_name;
  std::string m_description;

  ModelItem *m_parent;

  // wxTreeItemId *m_treeParent{};
};