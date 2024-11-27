#include <wx/wx.h>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"
#include "ui/mainWindow.hpp"

class MyApp : public wxApp {
public:
  bool OnInit() override {
    m_frame = new MyFrame;
    m_frame->Show(true);

    instantiateModels();

    return true;
  }

private:
  void instantiateModels() {
    m_sampleModel = new SampleModel;
    m_powerSubsystem = new PowerSubsystem;
  }

  MyFrame *m_frame{};

  SampleModel *m_sampleModel{};
  PowerSubsystem *m_powerSubsystem{};
};

// Main function is set here
wxIMPLEMENT_APP(MyApp); // NOLINT(cppcoreguidelines-pro-type-static-cast-downcast)