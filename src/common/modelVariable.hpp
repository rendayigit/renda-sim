#pragma once

#include <wx/listctrl.h>
#include <wx/wx.h>

#include "common/model.hpp"
#include "common/modelItem.hpp"

template <typename t> class ModelVariable : public ModelItem {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : ModelItem(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
  }

  void setValue(t value) {
    m_value = value;

    if (not m_isMonitored) {
      return;
    }

    wxTheApp->CallAfter( // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
        [&] { m_variableList->SetItem(m_treeIndex, 2, std::to_string(m_value)); });
  }

  t getValue() { return m_value; }

private:
  friend class MainWindow;
  void setMonitor(long index, wxListCtrl *variableList) {
    m_treeIndex = index;
    m_variableList = variableList;
    m_isMonitored = true;
  }

  void clearMonitor() { m_isMonitored = false; }

  t m_value;

  bool m_isMonitored{};
  long m_treeIndex = 0;
  wxListCtrl *m_variableList{};
};