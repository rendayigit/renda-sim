#pragma once

#include <string>
#include <utility>
#include <wx/treectrl.h>

class ModelItem {
public:
  explicit ModelItem(std::string name, std::string description, ModelItem *parent)
      : m_name(std::move(name)), m_description(std::move(description)), m_parent(parent) {}

  std::string getName() const { return m_name; }
  std::string getDescription() const { return m_description; }

  ModelItem *getParent() const { return m_parent; }

  wxTreeItemId getTreeParentId() const { return m_treeParentId; }

private:
  std::string m_name;
  std::string m_description;

  ModelItem *m_parent;

  wxTreeItemId m_treeParentId{};
};