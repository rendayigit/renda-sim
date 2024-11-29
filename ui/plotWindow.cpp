#include "ui/plotWindow.hpp"
#include "wx/brush.h"
#include "wx/gtk/brush.h"

#include <thread>

std::thread sinThread;
std::thread cosThread;

void drawSin(mpWindow *plotWindow, mpFXYVector *plot) {
  static std::vector<double> x;
  static std::vector<double> y;
  int i = 0;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Sample data
    plot->AddData(i, sin((double)i / 10), x, y);
    plotWindow->Fit();
    i++;
  }
}

void drawCos(mpWindow *plotWindow, mpFXYVector *plot) {
  static std::vector<double> x;
  static std::vector<double> y;
  int i = 0;

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(10));

    // Sample data
    plot->AddData(i, cos((double)i / 10) - 1, x, y);
    plotWindow->Fit();
    i++;
  }
}

PlotWindow::PlotWindow(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Plotter", wxDefaultPosition, wxSize(800, 600)) {
  auto *plotWindow = new mpWindow(this, wxID_ANY);

  plotWindow->SetBackgroundColour(wxColour(32, 32, 32));

  auto *sinPlot = new mpFXYVector();
  sinPlot->SetName("Sine");
  sinPlot->SetContinuity(true);

  auto *cosPlot = new mpFXYVector();
  cosPlot->SetName("Cosine");
  cosPlot->SetContinuity(true);

  auto redPen = wxPen(wxColour(255, 0, 0), 3);
  sinPlot->SetPen(redPen);

  auto greenPen = wxPen(wxColour(0, 255, 0), 3);
  cosPlot->SetPen(greenPen);

  auto font = wxFont(12, wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
  sinPlot->SetFont(font);
  cosPlot->SetFont(font);

  // Set name colors
  sinPlot->SetBrush(wxBrush(wxColour(255, 0, 0))); // Red for sine name
  cosPlot->SetBrush(wxBrush(wxColour(0, 255, 0))); // Green for cosine name

  plotWindow->AddLayer(sinPlot);
  plotWindow->AddLayer(cosPlot);

  plotWindow->Show();

  sinThread = std::thread(drawSin, plotWindow, sinPlot);
  cosThread = std::thread(drawCos, plotWindow, cosPlot);
}
