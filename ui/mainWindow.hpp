#pragma once

#include <mutex>
#include <wx/listctrl.h>
#include <wx/treectrl.h>
#include <wx/wx.h>

#include "services/scheduler/scheduler.hpp"

class MainWindow : public wxFrame {
public:
  static MainWindow &getInstance() {
    static MainWindow instance;
    return instance;
  }

  void logMessage(const std::string &message);
  void updateSimTime(const std::string &time);

private:
  MainWindow();

  void onStartStopClicked(wxCommandEvent &event);
  void onResetClicked(wxCommandEvent &event);
  void onStepClicked(wxCommandEvent &event);
  void onStoreClicked(wxCommandEvent &event);
  void onRestoreClicked(wxCommandEvent &event);
  void onTreeItemClicked(wxTreeEvent &event);

  void onExit(wxCommandEvent &event);
  void onAbout(wxCommandEvent &event);

  std::mutex m_mutex;

  Scheduler *m_scheduler;

  wxButton *m_startStopButton;
  wxButton *m_resetButton;
  wxButton *m_stepButton;
  wxButton *m_storeButton;
  wxButton *m_restoreButton;

  wxTextCtrl *m_simTimeDisplay;

  wxTreeCtrl *m_modelsTree;

  wxListCtrl *m_variableList;

  wxTextCtrl *m_logs;
};
