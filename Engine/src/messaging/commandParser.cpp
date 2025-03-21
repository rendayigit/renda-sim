#include "messaging/commandParser.hpp"

#include "logger/logger.hpp"
#include "messaging/commanding.hpp"
#include "model/modelContainer.hpp"
#include "scheduler/scheduler.hpp"

// TODO implement error handling for all received json data
// TODO refactor replyStatus["status"]s, some of them are redundant

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

  m_functionMap["RUN_FOR"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().runFor(command["millis"]);

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["STOP_IN"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stopIn(command["millis"]);

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["RUN_UNTIL"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().runUntil(command["time"]);

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["STOP_AT"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().stopAt(command["time"]);

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["STEP"] = [](const nlohmann::json &command) {
    Scheduler::getInstance().step();

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = Scheduler::getInstance().isRunning();
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
    std::string variablePath = command["variablePath"];

    auto *variable = ModelContainer::getInstance().getModel(variablePath);

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["variable"] = variable->getJson();
    replyStatus["status"] = true;

    variable->setMonitored(true);
    Logger::debug("Added " + variablePath + " to the monitor list.");

    Commanding::getInstance().reply(replyStatus.dump());
  };

  m_functionMap["VARIABLE_REMOVE"] = [](const nlohmann::json &command) {
    std::string variablePath = command["variablePath"];

    auto *variable = ModelContainer::getInstance().getModel(variablePath);

    if (variable != nullptr) {
      variable->setMonitored(false);
      Logger::debug("Removed " + variablePath + " from the monitor list.");
    }

    nlohmann::json replyStatus;
    replyStatus["command"] = command["command"];
    replyStatus["status"] = true;
    Commanding::getInstance().reply(replyStatus.dump());
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

  nlohmann::json message;
  message["command"] = command["command"];
  message["status"] = -1;
  Commanding::getInstance().reply(message.dump());
}