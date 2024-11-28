#include <string>

#include "common/model.hpp"
#include "common/modelVariable.hpp"
#include "mainWindow.hpp"
#include "services/modelContainer.hpp"
#include "services/serviceContainer.hpp"
#include "ui/variableTreeItemsContainer.hpp"

enum {
  ID_START_STOP_BTN = 1,
  ID_START_STOP_MENU,
  ID_RESET_BTN,
  ID_STEP_BTN,
  ID_STORE_BTN,
  ID_RESTORE_BTN,
  ID_MODELS_TREE,
  ID_VARIABLES_LIST
};

constexpr int TOP_BAR_COMP_HEIGHT = 30;

MainWindow::MainWindow()
    : wxFrame(nullptr, wxID_ANY, "Renda Sim"), m_scheduler(ServiceContainer::getInstance().scheduler()) {
  auto *menuFile = new wxMenu;
  menuFile->Append(ID_START_STOP_MENU, "Start / Stop", "Start or stop simulation");
  menuFile->Append(wxID_ANY, "Stop At", "Stop simulation at given time");
  menuFile->Append(wxID_ANY, "Stop In", "Stop simulation in given amount of time");
  menuFile->Append(wxID_ANY, "Reset", "Reset simulation");
  menuFile->Append(wxID_ANY, "Step", "Run simulation 1 step");
  menuFile->Append(wxID_ANY, "Run For", "Run simulation for given amount of time");
  menuFile->Append(wxID_ANY, "Run Until", "Run simulation until given time");
  menuFile->Append(wxID_ANY, "Store", "Store current simulation state");
  menuFile->Append(wxID_ANY, "Restore", "Restore simulation state from file");
  menuFile->Append(wxID_ANY, "Speed", "Set simulation speed");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_ANY, "Settings", "Open settings");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  auto *menuVariables = new wxMenu;
  menuVariables->Append(wxID_ANY, "Graph View", "Open Graph View");
  menuVariables->Append(wxID_ANY, "Save Variables", "Save variables to file");
  menuVariables->Append(wxID_ANY, "Load Variables", "Load variables from file");
  menuVariables->Append(wxID_ANY, "Clear", "Clear variables");

  auto *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuVariables, "&Variable Display");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Simulator ready");

  auto *verticalSizer = new wxBoxSizer(wxVERTICAL);
  auto *topHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
  auto *middleHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);

  m_startStopButton = new wxButton(
      this, ID_START_STOP_BTN, "Start", {},
      wxSize(100, TOP_BAR_COMP_HEIGHT)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  m_startStopButton->SetBackgroundColour(wxColour("#ffcc00"));
  m_startStopButton->SetForegroundColour(
      wxColour(wxSystemSettingsNative::GetAppearance().IsDark() ? "black" : "wxSYS_COLOUR_WINDOWTEXT"));

  m_resetButton = new wxButton(
      this, ID_RESET_BTN, "Reset", {},
      wxSize(100, TOP_BAR_COMP_HEIGHT)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  m_resetButton->SetBackgroundColour(wxColour("#ff4545"));
  m_resetButton->SetForegroundColour(wxColour("white"));

  m_stepButton = new wxButton(
      this, ID_STEP_BTN, "Step", {},
      wxSize(100, TOP_BAR_COMP_HEIGHT)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  m_storeButton = new wxButton(
      this, ID_STORE_BTN, "Store", {},
      wxSize(100, TOP_BAR_COMP_HEIGHT)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  m_restoreButton = new wxButton(
      this, ID_RESTORE_BTN, "Restore", {},
      wxSize(100, TOP_BAR_COMP_HEIGHT)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  auto *simTimeLabel = new wxStaticText(this, wxID_ANY, "Simulation Time (s) ");

  m_simTimeDisplay = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);

  m_logs = new wxTextCtrl(this, wxID_ANY, "", {},
                          wxSize(1200, 100), // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
                          wxTE_READONLY | wxTE_MULTILINE); // NOLINT(hicpp-signed-bitwise)

  m_modelsTree =
      new wxTreeCtrl(this, ID_MODELS_TREE, {},
                     wxSize(300, 400)); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  VariableTreeItemsContainer::getInstance().setModelsTree(m_modelsTree);

  m_variableList =
      new wxListCtrl(this, ID_VARIABLES_LIST, {}, wxSize(1000, 400),
                     wxLC_REPORT); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  m_variableList->InsertColumn(0, "Variable", wxLIST_FORMAT_LEFT, 200);
  m_variableList->InsertColumn(1, "Description", wxLIST_FORMAT_LEFT, 400);
  m_variableList->InsertColumn(2, "Value", wxLIST_FORMAT_LEFT, 150);
  m_variableList->InsertColumn(3, "Type", wxLIST_FORMAT_LEFT, 100);

  topHorizontalSizer->Add(m_startStopButton, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->Add(m_resetButton, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->Add(m_stepButton, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->Add(m_storeButton, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->Add(m_restoreButton, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->AddStretchSpacer();

  topHorizontalSizer->Add(simTimeLabel, 0, wxALIGN_CENTER_VERTICAL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  topHorizontalSizer->Add(m_simTimeDisplay, 0, wxALIGN_CENTER_VERTICAL, // NOLINT(bugprone-suspicious-enum-usage)
                          5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  middleHorizontalSizer->Add(m_modelsTree, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                             5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  middleHorizontalSizer->Add(m_variableList, 1, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                             5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  verticalSizer->Add(topHorizontalSizer, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                     5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  verticalSizer->Add(middleHorizontalSizer, 1, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                     5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  verticalSizer->Add(m_logs, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                     5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  SetSizer(verticalSizer);

  verticalSizer->Fit(this);
  verticalSizer->SetSizeHints(this);

  Bind(wxEVT_BUTTON, &MainWindow::onStartStopClicked, this, ID_START_STOP_BTN);
  Bind(wxEVT_BUTTON, &MainWindow::onResetClicked, this, ID_RESET_BTN);
  Bind(wxEVT_BUTTON, &MainWindow::onStepClicked, this, ID_STEP_BTN);
  Bind(wxEVT_BUTTON, &MainWindow::onStoreClicked, this, ID_STORE_BTN);
  Bind(wxEVT_BUTTON, &MainWindow::onRestoreClicked, this, ID_RESTORE_BTN);

  Bind(wxEVT_MENU, &MainWindow::onStartStopClicked, this, ID_START_STOP_MENU);
  Bind(wxEVT_MENU, &MainWindow::onAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MainWindow::onExit, this, wxID_EXIT);

  m_modelsTree->Bind(wxEVT_TREE_SEL_CHANGED, &MainWindow::onTreeItemClicked, this);
}

void MainWindow::logMessage(const std::string &message) {
  std::lock_guard<std::mutex> lock(m_mutex);
  wxTheApp->CallAfter([this, message] { // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
    wxString currentText = m_logs->GetValue() + message + "\n";
    wxArrayString lines = wxSplit(currentText, '\n');

    // If the number of lines exceeds limit, trim the excess lines
    while (lines.size() > 1000) {
      lines.RemoveAt(0, 1);
    }

    // Join the lines back together
    wxString newText = wxJoin(lines, '\n');
    m_logs->SetValue(newText);

    // Auto-scroll to the end
    m_logs->ShowPosition(m_logs->GetLastPosition());
  });
}

void MainWindow::updateSimTime(long time) {
  wxTheApp->CallAfter( // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)
      [this, time] { m_simTimeDisplay->SetValue(std::to_string(static_cast<double>(time) / 1000.0)); });
}

void MainWindow::onStartStopClicked(wxCommandEvent & /*event*/) {
  if (m_scheduler->isRunning()) {
    m_scheduler->stop();
    m_startStopButton->SetLabel("Start");
  } else {
    m_scheduler->start();
    m_startStopButton->SetLabel("Stop");
  }
}

void MainWindow::onResetClicked(wxCommandEvent & /*event*/) {
  m_scheduler->stop();
  m_startStopButton->SetLabel("Start");
  m_scheduler->reset();
}

void MainWindow::onStepClicked(wxCommandEvent & /*event*/) {}

void MainWindow::onStoreClicked(wxCommandEvent & /*event*/) {}

void MainWindow::onRestoreClicked(wxCommandEvent & /*event*/) {}

void MainWindow::onTreeItemClicked(wxTreeEvent &event) {
  wxTreeItemId selectedItem = event.GetItem();
  wxString selectedItemText = m_modelsTree->GetItemText(selectedItem);

  ModelItem *modelItem = ModelContainer::getInstance().getModel(selectedItemText.ToStdString());
  if (modelItem != nullptr) {
    auto *model = dynamic_cast<Model *>(modelItem);

    auto *doubleVariable = dynamic_cast<ModelVariable<double> *>(modelItem);
    auto *integerVariable = dynamic_cast<ModelVariable<int> *>(modelItem);
    auto *boolVariable = dynamic_cast<ModelVariable<bool> *>(modelItem);
    auto *stringVariable = dynamic_cast<ModelVariable<std::string> *>(modelItem);

    if (model != nullptr) {
      return;
    }

    if (doubleVariable != nullptr) {
      if (doubleVariable->m_isMonitored) {
        return;
      }

      long itemIndex = m_variableList->InsertItem(m_variableList->GetItemCount(), doubleVariable->getName());
      m_variableList->SetItem(itemIndex, 1, doubleVariable->getDescription());
      m_variableList->SetItem(itemIndex, 2, std::to_string(doubleVariable->getValue()));
      m_variableList->SetItem(itemIndex, 3, "Double");

      doubleVariable->setMonitor(itemIndex, m_variableList);
    } else if (integerVariable != nullptr) {
      if (integerVariable->m_isMonitored) {
        return;
      }

      long itemIndex = m_variableList->InsertItem(m_variableList->GetItemCount(), integerVariable->getName());
      m_variableList->SetItem(itemIndex, 1, integerVariable->getDescription());
      m_variableList->SetItem(itemIndex, 2, std::to_string(integerVariable->getValue()));
      m_variableList->SetItem(itemIndex, 3, "Integer");

      integerVariable->setMonitor(itemIndex, m_variableList);
    } else if (boolVariable != nullptr) {
      if (boolVariable->m_isMonitored) {
        return;
      }

      long itemIndex = m_variableList->InsertItem(m_variableList->GetItemCount(), boolVariable->getName());
      m_variableList->SetItem(itemIndex, 1, boolVariable->getDescription());
      m_variableList->SetItem(itemIndex, 2, boolVariable->getValue() ? "True" : "False");
      m_variableList->SetItem(itemIndex, 3, "Boolean");

      boolVariable->setMonitor(itemIndex, m_variableList);
    } else if (stringVariable != nullptr) {
      if (stringVariable->m_isMonitored) {
        return;
      }

      long itemIndex = m_variableList->InsertItem(m_variableList->GetItemCount(), stringVariable->getName());
      m_variableList->SetItem(itemIndex, 1, stringVariable->getDescription());
      m_variableList->SetItem(itemIndex, 2, stringVariable->getValue());
      m_variableList->SetItem(itemIndex, 3, "String");

      stringVariable->setMonitor(itemIndex, m_variableList);
    }
  } else {
    std::cout << selectedItemText << " is nullptr" << std::endl; // TODO(renda): handle
  }
}

void MainWindow::onExit(wxCommandEvent & /*event*/) { Close(true); }

void MainWindow::onAbout(wxCommandEvent & /*event*/) {
  wxMessageBox(
      "This is a simulator designed by Renda, see \nhttps://github.com/rendayigit/renda-sim \nfor more details.",
      "About Renda Sim", wxOK | wxICON_INFORMATION);
}