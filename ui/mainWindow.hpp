#pragma once

#include <wx/wx.h>

#include "services/scheduler/scheduler.hpp"

class MyFrame : public wxFrame {
public:
  MyFrame();

private:
  void onStartStopClicked(wxCommandEvent &event);
  void onResetClicked(wxCommandEvent &event);
  void onStepClicked(wxCommandEvent &event);
  void onStoreClicked(wxCommandEvent &event);
  void onRestoreClicked(wxCommandEvent &event);
  void onHello(wxCommandEvent &event);
  void onExit(wxCommandEvent &event);
  void onAbout(wxCommandEvent &event);

  Scheduler *m_scheduler;

  wxButton *m_startStopButton;
  wxButton *m_resetButton;
  wxButton *m_stepButton;
  wxButton *m_storeButton;
  wxButton *m_restoreButton;
};
