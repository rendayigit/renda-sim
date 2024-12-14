#include "common/load/load.hpp"
#include "common/load/loadContainer.hpp"
#include "common/load/loadState.hpp"
#include "services/fileOperations/fileOperations.hpp"
#include "services/json/json.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>

std::string testLoadConfigFile =
    FileOperations::getInstance().getExecutableDirectory() + "../tests/testLoadConfig.json";

class LoadTestModel : public Load {
public:
  LoadTestModel() : Load("Load Test Load", testLoadConfigFile) {
    auto *onState = new LoadState(testLoadConfigFile, ON_STATE);
    auto *offState = new LoadState(testLoadConfigFile, OFF_STATE);

    addState(onState);
    addState(offState);
  }

  void updateVbusIn(double value) override {}
  void updateVbusGnd(double value) override {}
};

TEST(Load, SetAndGetStates) {
  LoadTestModel testModel;

  EXPECT_EQ(testModel.getActiveState(), nullptr);

  testModel.setActiveState(ON_STATE);
  EXPECT_EQ(testModel.getActiveState()->getStateName(), ON_STATE);

  testModel.setActiveState(OFF_STATE);
  EXPECT_EQ(testModel.getActiveState()->getStateName(), OFF_STATE);
}

TEST(Load, SetAndGetParameters) {
  LoadTestModel testModel;

  // ON State
  testModel.setActiveState(ON_STATE);
  EXPECT_EQ(testModel.getActiveState()->getStateName(), ON_STATE);

  EXPECT_EQ(testModel.getActiveState()->getNominalVoltageConsumption(), 100.0);
  EXPECT_EQ(testModel.getActiveState()->getMinVoltageConsumption(), 95.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxVoltageConsumption(), 110.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalPowerConsumption(), 5.0);
  EXPECT_EQ(testModel.getActiveState()->getMinPowerConsumption(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxPowerConsumption(), 10.0);

  // OFF State
  testModel.setActiveState(OFF_STATE);
  EXPECT_EQ(testModel.getActiveState()->getStateName(), OFF_STATE);

  EXPECT_EQ(testModel.getActiveState()->getNominalVoltageConsumption(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMinVoltageConsumption(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxVoltageConsumption(), 0.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalTemperature(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMinTemperature(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxTemperature(), 0.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalPowerConsumption(), 1.5);
  EXPECT_EQ(testModel.getActiveState()->getMinPowerConsumption(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxPowerConsumption(), 2.0);

  EXPECT_EQ(testModel.getBusType(), BusType::PRIMARY);
}

TEST(Load, ErrorHandling) {
  LoadTestModel testModel;

  EXPECT_THROW(testModel.setActiveState("INVALID"), std::invalid_argument);

  auto *onState = new LoadState(testLoadConfigFile, ON_STATE);
  EXPECT_THROW(testModel.addState(onState), std::invalid_argument);

  EXPECT_THROW(testModel.updateState(15), std::runtime_error);

  testModel.setActiveState(ON_STATE);
  testModel.updateState(NAN);
  EXPECT_EQ(testModel.activeVoltageConsumption.getValue(), 0.0);

  EXPECT_THROW(testModel.getActiveState()->setTemperatureParameters(-1, -1, -1), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setTemperatureParameters(0, 0, 5), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setVoltageParameters(-15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setVoltageParameters(15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setPowerParameters(20.0, 10.0, 100.0), std::invalid_argument);

  EXPECT_NO_THROW(LoadContainer::getInstance().addLoad(nullptr));
  EXPECT_NO_THROW(LoadContainer::getInstance().removeLoad(nullptr));
}