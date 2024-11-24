#include "mainWindow.hpp"
#include "services/serviceContainer.hpp"

enum { ID_HELLO = 1, ID_START_STOP_BTN, ID_RESET_BTN, ID_STEP_BTN, ID_STORE_BTN, ID_RESTORE_BTN };

constexpr int TOP_BAR_COMP_HEIGHT = 30;

MyFrame::MyFrame()
    : wxFrame(nullptr, wxID_ANY, "Hello World"), m_scheduler(ServiceContainer::getInstance().scheduler()) {
  auto *menuFile = new wxMenu;
  menuFile->Append(ID_HELLO, "&Hello...\tCtrl-H", "Help string shown in status bar for this menu item");
  menuFile->AppendSeparator();
  menuFile->Append(wxID_EXIT);

  auto *menuHelp = new wxMenu;
  menuHelp->Append(wxID_ABOUT);

  auto *menuBar = new wxMenuBar;
  menuBar->Append(menuFile, "&File");
  menuBar->Append(menuHelp, "&Help");

  SetMenuBar(menuBar);

  CreateStatusBar();
  SetStatusText("Welcome to wxWidgets!");

  auto *verticalSizer = new wxBoxSizer(wxVERTICAL);
  auto *topHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);

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

  auto *logs =
      new wxTextCtrl(this, wxID_ANY, "", {},
                     wxSize(400, 400), // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)
                     wxTE_READONLY | wxTE_MULTILINE); // NOLINT(hicpp-signed-bitwise)

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

  verticalSizer->Add(topHorizontalSizer, 0, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                     5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  verticalSizer->Add(logs, 1, wxEXPAND | wxALL, // NOLINT(bugprone-suspicious-enum-usage)
                     5); // NOLINT(cppcoreguidelines-avoid-magic-numbers, readability-magic-numbers)

  SetSizer(verticalSizer);

  verticalSizer->Fit(this);
  verticalSizer->SetSizeHints(this);

  Bind(wxEVT_BUTTON, &MyFrame::onStartStopClicked, this, ID_START_STOP_BTN);
  Bind(wxEVT_BUTTON, &MyFrame::onResetClicked, this, ID_RESET_BTN);
  Bind(wxEVT_BUTTON, &MyFrame::onStepClicked, this, ID_STEP_BTN);
  Bind(wxEVT_BUTTON, &MyFrame::onStoreClicked, this, ID_STORE_BTN);
  Bind(wxEVT_BUTTON, &MyFrame::onRestoreClicked, this, ID_RESTORE_BTN);

  Bind(wxEVT_MENU, &MyFrame::onHello, this, ID_HELLO);
  Bind(wxEVT_MENU, &MyFrame::onAbout, this, wxID_ABOUT);
  Bind(wxEVT_MENU, &MyFrame::onExit, this, wxID_EXIT);
}

void MyFrame::onStartStopClicked(wxCommandEvent & /*event*/) {
  if (m_scheduler->isRunning()) {
    m_scheduler->stop();
    m_startStopButton->SetLabel("Start");
  } else {
    m_scheduler->start();
    m_startStopButton->SetLabel("Stop");
  }
}

void MyFrame::onResetClicked(wxCommandEvent & /*event*/) {}
void MyFrame::onStepClicked(wxCommandEvent & /*event*/) {}
void MyFrame::onStoreClicked(wxCommandEvent & /*event*/) {}
void MyFrame::onRestoreClicked(wxCommandEvent & /*event*/) {}

void MyFrame::onExit(wxCommandEvent & /*event*/) { Close(true); }

void MyFrame::onAbout(wxCommandEvent & /*event*/) {
  wxMessageBox("This is a wxWidgets Hello World example", "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::onHello(wxCommandEvent & /*event*/) { wxLogMessage("Hello world from wxWidgets!"); }
