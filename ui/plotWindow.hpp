#pragma once

#include <mathplot.h>
#include <vector>
#include <wx/wx.h>

class PlotWindow : public wxFrame {
public:
  explicit PlotWindow(wxWindow *parent);

  void updatePlot() {}

private:
  std::vector<std::vector<double>> m_data;
};
