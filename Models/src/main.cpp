#include "engine.hpp"

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  // SampleModel sampleModel;
  PowerSubsystem powerSubsystem;

  // Start engine
  Engine::run();

  return 0;
}
