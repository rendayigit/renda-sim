#include "common/load/load.hpp"
#include "common/load/loadContainer.hpp"
#include "common/load/loadState.hpp"
#include "services/fileOperations.hpp"
#include "services/json/json.hpp"
#include <cmath>
#include <gtest/gtest.h>
#include <stdexcept>

std::string testLoadConfigFile =
    FileOperations::getInstance().getExecutableDirectory() + "tests/models/testLoadConfig.json";

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

  EXPECT_EQ(testModel.getActiveState()->getNominalCurrentConsumption(), 0.2);
  EXPECT_EQ(testModel.getActiveState()->getMinCurrentConsumption(), 0.03);
  EXPECT_EQ(testModel.getActiveState()->getMaxCurrentConsumption(), 0.25);

  EXPECT_EQ(testModel.getActiveState()->getNominalVoltageConsumption(), 10.0);
  EXPECT_EQ(testModel.getActiveState()->getMinVoltageConsumption(), 3.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxVoltageConsumption(), 28.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalHeatDissipation(), 5.0);
  EXPECT_EQ(testModel.getActiveState()->getMinHeatDissipation(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxHeatDissipation(), 10.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalPowerConsumption(), 5.0);
  EXPECT_EQ(testModel.getActiveState()->getMinPowerConsumption(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxPowerConsumption(), 10.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalResistance(), 100E3);
  EXPECT_EQ(testModel.getActiveState()->getMinResistance(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxResistance(), 100E6);

  testModel.getActiveState()->setNominalResistance(100E4);
  EXPECT_EQ(testModel.getActiveState()->getNominalResistance(), 100E4);
  testModel.getActiveState()->setNominalResistance(100E3);

  // OFF State
  testModel.setActiveState(OFF_STATE);
  EXPECT_EQ(testModel.getActiveState()->getStateName(), OFF_STATE);

  EXPECT_EQ(testModel.getActiveState()->getNominalCurrentConsumption(), 0.05);
  EXPECT_EQ(testModel.getActiveState()->getMinCurrentConsumption(), 0.01);
  EXPECT_EQ(testModel.getActiveState()->getMaxCurrentConsumption(), 0.1);

  EXPECT_EQ(testModel.getActiveState()->getNominalVoltageConsumption(), 1.2);
  EXPECT_EQ(testModel.getActiveState()->getMinVoltageConsumption(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxVoltageConsumption(), 1.5);

  EXPECT_EQ(testModel.getActiveState()->getNominalHeatDissipation(), 1.5);
  EXPECT_EQ(testModel.getActiveState()->getMinHeatDissipation(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxHeatDissipation(), 2.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalTemperature(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMinTemperature(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxTemperature(), 0.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalPowerConsumption(), 1.5);
  EXPECT_EQ(testModel.getActiveState()->getMinPowerConsumption(), 1.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxPowerConsumption(), 2.0);

  EXPECT_EQ(testModel.getActiveState()->getNominalResistance(), 100E3);
  EXPECT_EQ(testModel.getActiveState()->getMinResistance(), 0.0);
  EXPECT_EQ(testModel.getActiveState()->getMaxResistance(), 100E9);

  testModel.getActiveState()->setNominalResistance(100E8);
  EXPECT_EQ(testModel.getActiveState()->getNominalResistance(), 100E8);
  testModel.getActiveState()->setNominalResistance(100E3);

  EXPECT_EQ(testModel.getAlphaCoefficient(), 0.0);
  testModel.setAlphaCoefficient(1.0);
  EXPECT_EQ(testModel.getAlphaCoefficient(), 1.0);
  EXPECT_THROW(testModel.setAlphaCoefficient(-1), std::invalid_argument);

  EXPECT_EQ(testModel.getBusType(), BusType::PRIMARY);

  testModel.getActiveState()->setNominalResistance(10.0);
  testModel.activeTemperature.setValue(1);
  testModel.setAlphaCoefficient(1);
  EXPECT_EQ(testModel.getCorrectedResistance(), 0.0);
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

  EXPECT_THROW(testModel.getActiveState()->setCurrentParameters(15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setDissipationParameters(15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setTemperatureParameters(-1, -1, -1), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setTemperatureParameters(0, 0, 5), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setVoltageParameters(-15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setVoltageParameters(15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setResistanceParameters(-15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setResistanceParameters(15.0, 10.0, 30.0), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setNominalResistance(-1), std::invalid_argument);
  EXPECT_THROW(testModel.getActiveState()->setPowerParameters(20.0, 10.0, 100.0), std::invalid_argument);

  EXPECT_NO_THROW(LoadContainer::getInstance().addLoad(nullptr));
  EXPECT_NO_THROW(LoadContainer::getInstance().removeLoad(nullptr));
}