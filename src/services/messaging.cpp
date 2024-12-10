#include "services/messaging.hpp"

#include <iostream> // TODO(renda): Remove after testing
#include <string>

#include "common/modelVariable.hpp"
#include "common/variableProperties.hpp"
#include "services/messageParser.hpp"
#include "services/modelContainer.hpp"
#include "services/serviceContainer.hpp"

constexpr int MESSAGING_MAX_COMMAND_SIZE = 1024;
constexpr int MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION = 100;

Messaging::~Messaging() {
  m_isCommandReceiverThreadRunning = false;

  if (m_commandReceiverThread.joinable()) {
    m_commandReceiverThread.join();
  }

  delete m_publisher;
  delete m_publisherContext;
}

void Messaging::queueMessage(const std::string &topic, const std::string &message) {
  zmq::message_t zTopic(topic.data(), topic.size());
  zmq::message_t zMessage(message.data(), message.size());

  m_publisher->send(zTopic, zmq::send_flags::sndmore);
  m_publisher->send(zMessage, zmq::send_flags::none);
}

void Messaging::reply(const std::string &message) { m_commandReceiver->send(zmq::buffer(message)); }

void Messaging::commandReceiverStep() {
  while (m_isCommandReceiverThreadRunning) {
    std::array<char, MESSAGING_MAX_COMMAND_SIZE> buf{'\0'};
    zmq::mutable_buffer request(buf.data(), buf.size());
    zmq::recv_buffer_result_t result = m_commandReceiver->recv(request, zmq::recv_flags::none);

    std::string command = static_cast<char *>(request.data());

    std::cout << "Received: " << command << std::endl; // TODO(renda): Remove after testing

    // TODO(renda): Move to MessageParser
    if (command == "STATUS") {
      Messaging::getInstance().reply("ENGINE ONLINE");
      continue;
    }

    // TODO(renda): Move to MessageParser
    if (command == "SCHEDULER_STATUS") {
      Messaging::getInstance().reply(ServiceContainer::getInstance().scheduler()->isRunning() ? "RUNNING" : "STOPPED");
      continue;
    }

    // TODO(renda): Move to MessageParser
    if (command == "MODEL_TREE") {
      Messaging::getInstance().reply(ModelContainer::getInstance().getModelTreeJson().dump());
      continue;
    }

    // TODO(renda): Move to MessageParser
    if (command.find("START_LISTEN") != std::string::npos) {
      size_t colonPosition = command.find(':');

      if (colonPosition != std::string::npos) {
        // Get the substring after the colon
        std::string variablePath = command.substr(colonPosition + 1);

        auto *object = ModelContainer::getInstance().getModel(variablePath);

        auto *doubleVariable = dynamic_cast<ModelVariable<double> *>(object);
        auto *integerVariable = dynamic_cast<ModelVariable<int> *>(object);
        auto *boolVariable = dynamic_cast<ModelVariable<bool> *>(object);
        auto *stringVariable = dynamic_cast<ModelVariable<std::string> *>(object);

        std::string reply;

        if (doubleVariable != nullptr) {
          reply = doubleVariable->getDescription() + ":" + std::to_string(doubleVariable->getValue()) + ":" + "Double";
        } else if (integerVariable != nullptr) {
          reply =
              integerVariable->getDescription() + ":" + std::to_string(integerVariable->getValue()) + ":" + "Integer";
        } else if (boolVariable != nullptr) {
          reply =
              boolVariable->getDescription() + ":" + (boolVariable->getValue() ? "True" : "False") + ":" + "Boolean";
        } else if (stringVariable != nullptr) {
          reply = stringVariable->getDescription() + ":" + stringVariable->getValue() + ":" + "String";
        }

        std::cout << reply << std::endl; // TODO(renda): Remove after testing
        Messaging::getInstance().reply(reply);

        // Start monitoring
        auto *variable = dynamic_cast<VariableProperties *>(object);
        variable->setIsMonitored(true);
      }
    }

    MessageParser::getInstance().executeCommand(command);

    std::this_thread::sleep_for(std::chrono::milliseconds(MESSAGING_COMMAND_RECEIVER_SLEEP_DURATION));
  }
}