#include <iostream>

#include "sampleModel/sampleModel.hpp"
#include "services/serviceContainer.hpp"

int main(int /*argc*/, char ** /*argv*/) {
  std::cout << "Simulation Start" << std::endl;

  ServiceContainer::getInstance().scheduler()->start();

  SampleModel sm;

  std::cin.get();

  return 0;
}
