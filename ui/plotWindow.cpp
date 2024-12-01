#include "ui/plotWindow.hpp"

PlotWindow::PlotWindow(wxWindow *parent)
    : wxFrame(parent, wxID_ANY, "Plotter", wxDefaultPosition, wxSize(800, 600)),
      m_plotWindow(new mpWindow(this, wxID_ANY)) {
  srand(time(0));

  m_colors.emplace_back(255, 0, 0);     // Red
  m_colors.emplace_back(0, 255, 0);     // Green
  m_colors.emplace_back(0, 0, 255);     // Blue
  m_colors.emplace_back(255, 255, 0);   // Yellow
  m_colors.emplace_back(255, 0, 255);   // Magenta
  m_colors.emplace_back(0, 255, 255);   // Cyan
  m_colors.emplace_back(255, 255, 255); // White
  m_colors.emplace_back(128, 0, 0);     // Maroon
  m_colors.emplace_back(128, 128, 0);   // Olive
  m_colors.emplace_back(128, 0, 128);   // Purple
  m_colors.emplace_back(0, 128, 128);   // Teal
  m_colors.emplace_back(192, 192, 192); // Silver

  m_font = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

  m_plotWindow->SetBackgroundColour(wxColour(32, 32, 32));
  m_plotWindow->SetMargins(0, 0, 30, 0);
}

PlotWindow::~PlotWindow() {
  m_plotWindow->DelAllLayers(true);

  m_plotWindow->Close();
  delete m_plotWindow;
}

void PlotWindow::addPlot(mpFXYVector *plot) {
  plot->SetContinuity(true);
  plot->SetPen(wxPen(m_colors.at(rand() % m_colors.size()), 3));
  plot->SetFont(m_font);
  m_plotWindow->AddLayer(plot);
}

void PlotWindow::fitPlot() {
  if (m_plotWindow != nullptr and m_plotWindow->CountLayers() > 0) {
    m_plotWindow->Fit();
  }
}

unsigned int PlotWindow::getPlotCount() {
    return m_plotWindow->CountAllLayers();
}
