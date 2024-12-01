#pragma once

#include <vector>
#include <wx/listctrl.h>
#include <wx/wx.h>

#include "common/model.hpp"
#include "common/modelItem.hpp"
#include "ui/plotWindow.hpp"

template <typename t> class ModelVariable : public ModelItem {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : ModelItem(name, description, parent), m_value(initialValue) {
    parent->addChild(this);
  }

  void setValue(t value) {
    m_value = value;

    if (m_isMonitored) {
      wxTheApp->CallAfter( // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
          [this, value] { m_variableList->SetItem(m_treeIndex, 2, std::to_string(value)); });
    }

    if (m_isPlotted) {
      static int i = 0;

      if (m_plotWindow == nullptr or m_plotWindow->getPlotCount() == 0) {
        m_isPlotted = false;
        return;
      }

      wxTheApp->CallAfter( // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
          [this, value] {
            m_plot->AddData(i, value, this->m_x, this->m_y);
            this->m_plotWindow->fitPlot();
            i++;
          });
    }
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

  void setPlot(PlotWindow *plotWindow) {
    m_plot = new mpFXYVector();
    m_plot->SetName(getName());
    plotWindow->addPlot(m_plot);

    m_plotWindow = plotWindow;
    m_isPlotted = true;
  }

  void clearPlot() { m_isPlotted = false; }

  t m_value;

  bool m_isMonitored{};
  bool m_isPlotted{};
  long m_treeIndex = 0;

  wxListCtrl *m_variableList{};

  mpFXYVector *m_plot{};
  PlotWindow *m_plotWindow{};
  std::vector<double> m_x;
  std::vector<double> m_y;
};