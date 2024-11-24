#include <wx/wx.h>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "ui/mainWindow.hpp"

class MyApp : public wxApp {
public:
  MyApp() : m_sampleModel(new SampleModel), m_powerSubsystem(new PowerSubsystem) {
    // TODO(renda): Call model init functions here
  }

  bool OnInit() override {
    m_frame = new MyFrame;

    m_powerSubsystem->logMessage = [&](const std::string &message) { m_frame->logMessage(message); };

    m_frame->Show(true);
    return true;
  }

private:
  MyFrame *m_frame{};

  SampleModel *m_sampleModel;
  PowerSubsystem *m_powerSubsystem;
};

// Main function is set here
wxIMPLEMENT_APP(MyApp); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)