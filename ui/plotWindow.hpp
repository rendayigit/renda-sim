#pragma once

#include <mathplot.h>
#include <thread>
#include <vector>
#include <wx/wx.h>

class PlotWindow : public wxFrame {
public:
  explicit PlotWindow(wxWindow *parent);
  ~PlotWindow() override {
    m_isOn = false;

    if (m_sinThread.joinable()) {
      m_sinThread.join();
    }

    if (m_cosThread.joinable()) {
      m_cosThread.join();
    }

    m_plotWindow->DelAllLayers(true);

    m_plotWindow->Close();
    delete m_plotWindow;
  }

  void updatePlot() {}

private:
  void drawSin() const;
  void drawCos() const;

  mpWindow *m_plotWindow;
  mpFXYVector *m_sinPlot;
  mpFXYVector *m_cosPlot;

  std::vector<std::vector<double>> m_data;

  bool m_isOn = true;
  std::thread m_sinThread;
  std::thread m_cosThread;
};
