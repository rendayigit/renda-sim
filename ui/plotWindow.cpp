#include "ui/plotWindow.hpp"
#include "wx/brush.h"
#include "wx/gtk/brush.h"

PlotWindow::PlotWindow(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Plotter", wxDefaultPosition, wxSize(800, 600)) {
  m_plotWindow = new mpWindow(this, wxID_ANY);

  m_plotWindow->SetBackgroundColour(wxColour(32, 32, 32));

  m_sinPlot = new mpFXYVector();
  m_sinPlot->SetName("Sine");
  m_sinPlot->SetContinuity(true);

  m_cosPlot = new mpFXYVector();
  m_cosPlot->SetName("Cosine");
  m_cosPlot->SetContinuity(true);

  auto redPen = wxPen(wxColour(255, 0, 0), 3);
  m_sinPlot->SetPen(redPen);

  auto greenPen = wxPen(wxColour(0, 255, 0), 3);
  m_cosPlot->SetPen(greenPen);

  auto font = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  m_sinPlot->SetFont(font);
  m_cosPlot->SetFont(font);

  // Set name colors
  m_sinPlot->SetBrush(wxBrush(wxColour(255, 0, 0))); // Red for sine name
  m_cosPlot->SetBrush(wxBrush(wxColour(0, 255, 0))); // Green for cosine name

  m_plotWindow->AddLayer(m_sinPlot);
  m_plotWindow->AddLayer(m_cosPlot);

  m_plotWindow->Show();

  m_sinThread = std::thread([this] { drawSin(); });
  m_cosThread = std::thread([this] { drawCos(); });
}

void PlotWindow::drawSin() const {
  static std::vector<double> x;
  static std::vector<double> y;
  int i = 0;

  while (m_isOn) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Sample data
    m_sinPlot->AddData(i, sin((double)i / 10), x, y);
    m_plotWindow->Fit();
    i++;
  }
}

void PlotWindow::drawCos() const {
  static std::vector<double> x;
  static std::vector<double> y;
  int i = 0;

  while (m_isOn) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Sample data
    m_cosPlot->AddData(i, cos((double)i / 10) - 1, x, y);
    m_plotWindow->Fit();
    i++;
  }
}
