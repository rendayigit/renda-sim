#include "root.hpp"

Root::Root() : m_sampleModel(new SampleModel()), m_powerSubsystem(new PowerSubsystem()) {}

void Root::init() {
  // Instantiate models
  // m_sampleModel->init();     // TODO(renda): Initialize models
  // m_powerSubsystem->init();  // TODO(renda): Initialize models
}

void Root::run() {
  // m_sampleModel->run();            // TODO(renda): Run models
  // m_powerSubsystem->run();         // TODO(renda): Run models
}
