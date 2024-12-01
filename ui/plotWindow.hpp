#pragma once

#include <mathplot.h>
#include <utility>
#include <vector>
#include <wx/wx.h>

class PlotWindow : public wxFrame {
public:
  explicit PlotWindow(wxWindow *parent);
  ~PlotWindow() override;

  void addPlot(mpFXYVector *plot);
  void fitPlot();
  unsigned int getPlotCount();

private:
  mpWindow *m_plotWindow;
  std::vector<wxColour> m_colors;
  wxFont m_font;
};
