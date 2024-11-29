#include "ui/plotWindow.hpp"

PlotWindow::PlotWindow(wxWindow *parent) : wxFrame(parent, wxID_ANY, "Plotter", wxDefaultPosition, wxSize(800, 600)) {
  auto *plotWindow = new mpWindow(this, wxID_ANY);

  // Sample data
  std::vector<double> x;
  std::vector<double> y;
  for (double i = 0; i < 100; i += 0.01) {
    x.push_back(i);
    y.push_back(sin(i));
  }

  auto *plot = new mpFXYVector();
  plot->SetData(x, y);

  plotWindow->AddLayer(plot);

  plotWindow->Fit();
  plotWindow->Show();
}
