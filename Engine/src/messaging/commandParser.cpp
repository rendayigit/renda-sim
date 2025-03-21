#include "messaging/commandParser.hpp"

#include "logger/logger.hpp"
#include "messaging/commanding.hpp"
#include "messaging/publisher.hpp"
#include "model/modelContainer.hpp"
#include "scheduler/scheduler.hpp"

// TODO implement error handling for all received json data

CommandParser::CommandParser() {
  m_functionMap["START"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().start();

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["STOP"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stop();

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["RUN_FOR"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().runFor(command["millis"]);

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["STOP_IN"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stopIn(command["millis"]);

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["RUN_UNTIL"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().runUntil(command["time"]);

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["STOP_AT"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stopAt(command["time"]);

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["STEP"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().step();

    Commanding::getInstance().reply("{}");
  };

  m_functionMap["STATUS"] = [](const nlohmann::json &command) {
    Commanding::getInstance().reply("{}");

    nlohmann::json status;
    status["schedulerIsRunning"] = Scheduler::getInstance().isRunning();
    Publisher::getInstance().queueMessage("STATUS", status);
  };

  m_functionMap["MODEL_TREE"] = [](const nlohmann::json &command) {
    nlohmann::json reply;
    reply["modelTree"] = ModelContainer::getInstance().getModelTreeJson();
    Commanding::getInstance().reply(reply.dump());
  };

  m_functionMap["VARIABLE_ADD"] = [](const nlohmann::json &command) {
    std::string variablePath = command["variablePath"];
    auto *variable = ModelContainer::getInstance().getModel(variablePath);

    if (variable == nullptr) {
      Logger::error(command["variablePath"].get<std::string>() + " is not a valid variable path");
      Commanding::getInstance().reply({});
      return;
    }

    variable->setMonitored(true);

    nlohmann::json reply;
    reply["variable"] = variable->getJson();
    Commanding::getInstance().reply(reply.dump());
  };

  m_functionMap["VARIABLE_REMOVE"] = [](const nlohmann::json &command) {
    std::string variablePath = command["variablePath"];
    auto *variable = ModelContainer::getInstance().getModel(variablePath);

    if (variable == nullptr) {
      Logger::error(command["variablePath"].get<std::string>() + " is not a valid variable path");
      Commanding::getInstance().reply({});
      return;
    }

    variable->setMonitored(false);

    Commanding::getInstance().reply("{}");
  };
}

void CommandParser::executeCommand(const nlohmann::json &command) {
  for (auto &function : m_functionMap) {
    if (command["command"].get<std::string>() == function.first) {
      function.second(command);
      return; // return after first match
    }
  }

  // return undefined if no match
  Logger::error("Undefined command: " + command.dump());

  Commanding::getInstance().reply("{}");
}