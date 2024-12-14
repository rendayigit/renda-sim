#include <iostream>

#include "pcs/pcs.hpp"
#include "sampleModel/sampleModel.hpp"

#include "engine/messaging/messaging.hpp"      // TODO(renda): Move somewhere else
#include "engine/model/modelContainer.hpp" // TODO(renda): Remove after testing

int main(int /*argc*/, char ** /*argv*/) {
  // Instantiate models
  SampleModel sm;
  PowerSubsystem powerSubsystem;

  // TODO(renda): All subsystems must be added to model container
  ModelContainer::getInstance().addModel(&sm);
  ModelContainer::getInstance().addModel(&powerSubsystem);

  // TODO(renda): Remove after testing
  std::cout << "Model Tree:" << std::endl;
  std::cout << ModelContainer::getInstance().getModelTreeJson().dump(2) << std::endl;

  Messaging::getInstance().queueMessage("SIM_TIME", "-"); // TODO(renda): Move somewhere else

  std::cout << "\nPress enter to stop the simulation\n\n";
  char input = 0;
  while (input != '\n') {
    std::cin.get(input);
  }

  return 0;
}
