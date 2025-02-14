#include "messaging/commandParser.hpp"

#include "logger/logger.hpp"
#include "messaging/commanding.hpp"
#include "model/modelContainer.hpp"
#include "model/modelVariable.hpp"
#include "model/variableProperties.hpp"
#include "scheduler/scheduler.hpp"

CommandParser::CommandParser() {
  m_functionMap["START"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().start();

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["STOP"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stop();

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = not Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["SCHEDULER"] = [](const nlohmann::json &command) {
    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["schedulerIsRunning"] = Scheduler::getInstance().isRunning();
    replyStatus["status"] = true;
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["MODEL_TREE"] = [](const nlohmann::json &command) {
    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["modelTree"] = ModelContainer::getInstance().getModelTreeJson();
    replyStatus["status"] = true;
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["VARIABLE_ADD"] = [](const nlohmann::json &command) {
    std::string variablePath = command["variablePath"]; // TODO implement error handling

    auto *object = ModelContainer::getInstance().getModel(variablePath);

    auto *doubleVariable = dynamic_cast<ModelVariable<double> *>(object);
    auto *integerVariable = dynamic_cast<ModelVariable<int> *>(object);
    auto *boolVariable = dynamic_cast<ModelVariable<bool> *>(object);
    auto *stringVariable = dynamic_cast<ModelVariable<std::string> *>(object);

    // TODO(renda): Add all primitive types
    /*
    void
    bool
    char
    short
    int
    long long
    long
    unsigned char
    unsigned short
    unsigned int
    unsigned long long
    unsigned long
    wchar_t
    float
    double
    */

    std::string reply;

    if (doubleVariable != nullptr) {
      reply = doubleVariable->getDescription() + "," + std::to_string(doubleVariable->getValue()) + "," + "Double";
      doubleVariable->setIsMonitored(true);
    } else if (integerVariable != nullptr) {
      reply = integerVariable->getDescription() + "," + std::to_string(integerVariable->getValue()) + "," + "Integer";
      integerVariable->setIsMonitored(true);
    } else if (boolVariable != nullptr) {
      reply = boolVariable->getDescription() + "," + (boolVariable->getValue() ? "True" : "False") + "," + "Boolean";
      boolVariable->setIsMonitored(true);
    } else if (stringVariable != nullptr) {
      reply = stringVariable->getDescription() + "," + stringVariable->getValue() + "," + "String";
      stringVariable->setIsMonitored(true);
    } else {
      Logger::debug(variablePath + " is not a valid variable path.");
    }

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["variable"] = reply;
    replyStatus["status"] = true; // TODO implement return value
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["VARIABLE_REMOVE"] = [](const nlohmann::json &command) {
    std::string variablePath = command["variablePath"]; // TODO implement error handling

    auto *object = ModelContainer::getInstance().getModel(variablePath);
    auto *variable = dynamic_cast<VariableProperties *>(object);

    if (variable != nullptr) {
      variable->setIsMonitored(false);
      Logger::debug("Removed " + variablePath + " from the monitor list.");
    }

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = true; // TODO implement return value
    Commanding::getInstance().reply(replyStatus.dump());
  };
}

void CommandParser::executeCommand(const nlohmann::json &command) {
  for (auto &function : m_functionMap) {
    if (command["command"].dump().find(function.first) != std::string::npos) {
      function.second(command);
      return; // return after first match
    }
  }

  // return undefined if no match
  Logger::error("Undefined command: " + command.dump());

  nlohmann::json message;
  message["command"] = command["command"];
  message["status"] = -1;
  Commanding::getInstance().reply(message.dump());
}