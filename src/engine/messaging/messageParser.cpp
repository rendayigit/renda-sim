#include "engine/messaging/messageParser.hpp"

#include "engine/model/modelVariable.hpp"
#include "engine/model/variableProperties.hpp"
#include "engine/messaging/messaging.hpp"
#include "engine/model/modelContainer.hpp"
#include "engine/scheduler/scheduler.hpp"

void MessageParser::executeCommand(const std::string &command) {
  for (auto &function : m_functionMap) {
    if (command.find(function.first) != std::string::npos) {
      std::string functionArguments;

      // Function arguments must be passed after a colon
      size_t colonPosition = command.find(':');

      // Get the substring after the colon
      if (colonPosition != std::string::npos) {
        functionArguments = command.substr(colonPosition + 1);
      }

      function.second(functionArguments);
    }
  }
}

MessageParser::MessageParser() {
  m_functionMap["START"] = [](const std::string & /*message*/) { Scheduler::getInstance().start(); };

  m_functionMap["STOP"] = [](const std::string & /*message*/) { Scheduler::getInstance().stop(); };

  m_functionMap["SCHEDULER"] = [](const std::string & /*message*/) {
    Messaging::getInstance().reply(Scheduler::getInstance().isRunning() ? "RUNNING" : "STOPPED");
  };

  m_functionMap["MODEL_TREE"] = [](const std::string & /*message*/) {
    Messaging::getInstance().reply(ModelContainer::getInstance().getModelTreeJson().dump());
  };

  m_functionMap["VARIABLE_ADD"] = [](const std::string &variablePath) {
    auto *object = ModelContainer::getInstance().getModel(variablePath);

    auto *doubleVariable = dynamic_cast<ModelVariable<double> *>(object);
    auto *integerVariable = dynamic_cast<ModelVariable<int> *>(object);
    auto *boolVariable = dynamic_cast<ModelVariable<bool> *>(object);
    auto *stringVariable = dynamic_cast<ModelVariable<std::string> *>(object);

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
      std::cout << variablePath << " is not a valid variable path." << std::endl;
    }

    Messaging::getInstance().reply(reply);
  };

  m_functionMap["VARIABLE_REMOVE"] = [](const std::string &variablePath) {
    auto *object = ModelContainer::getInstance().getModel(variablePath);
    auto *variable = dynamic_cast<VariableProperties *>(object);

    if (variable != nullptr) {
      variable->setIsMonitored(false);
      std::cout << "Removed " << variablePath << " from the monitor list."
                << std::endl; // TODO(renda): remove after testing
    }
  };
}