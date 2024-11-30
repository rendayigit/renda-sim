#pragma once

#include <mathplot.h>
#include <utility>
#include <vector>
#include <wx/wx.h>

class PlotWindow : public wxFrame {
public:
  explicit PlotWindow(wxWindow *parent);
  ~PlotWindow() override;

  void setPlots(std::vector<mpFXYVector *> plots);
  void fitPlot();

private:
  void drawSin() const;
  void drawCos() const;

  mpWindow *m_plotWindow;

  std::vector<std::vector<double>> m_data;
  std::vector<wxColour> m_colors;
};
