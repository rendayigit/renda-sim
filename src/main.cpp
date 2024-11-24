#include <wx/wx.h>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "ui/mainWindow.hpp"

class MyApp : public wxApp {
public:
  MyApp() : m_sampleModel(new SampleModel), m_powerSubsystem(new PowerSubsystem) {}

  bool OnInit() override {
    auto *frame = new MyFrame();
    frame->Show(true);
    return true;
  }

private:
  SampleModel *m_sampleModel;
  PowerSubsystem *m_powerSubsystem;
};

// Main function is set here
wxIMPLEMENT_APP(MyApp); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)