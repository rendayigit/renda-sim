#pragma once

#include <cxxabi.h>
#include <iostream>
#include <string>

#include "messaging/publisher.hpp"
#include "model/model.hpp"
#include "model/object.hpp"

// TODO improve
static std::string demangle(const char *name) {
  int status = -1;
  std::unique_ptr<char, void (*)(void *)> res{abi::__cxa_demangle(name, nullptr, nullptr, &status), std::free};

  if (status != 0) {
    return "UNKOWN TYPE";
  }

  std::string demangledName = res.get();

  if (demangledName.find("std::__cxx11::basic_string") != std::string::npos) {
    return "string";
  }

  if (demangledName.find("std::__cxx11::basic_string<") != std::string::npos) {
    return "string";
  }

  if (demangledName.find("std::vector") != std::string::npos) {
    return "vector";
  }

  if (demangledName.find("std::basic_string<") != std::string::npos) {
    return "string";
  }

  return demangledName;
}

template <typename t> class ModelVariable : public Object {
public:
  explicit ModelVariable(std::string name, std::string description, Model *parent, t initialValue)
      : Object(name, description, parent), m_value(initialValue) {
    if (parent != nullptr) {
      parent->addChild(this);
    } else {
      // TODO(renda): Log a better way
      std::cerr << "Variable " + name + " has no parent assigned" << std::endl;
    }
  }

  void setValue(t value) {
    m_value = value;

    if (isMonitored()) {
      nlohmann::json message;
      message["variablePath"] = getPath();
      message["variableValue"] = m_value;
      Publisher::getInstance().queueMessage("VARIABLE", message.dump());
    }
  }

  t getValue() { return m_value; }

  nlohmann::json getJson() override {
    nlohmann::json jsonVar;
    jsonVar["name"] = getName();
    jsonVar["path"] = getPath();
    jsonVar["description"] = getDescription();
    jsonVar["value"] = m_value;
    jsonVar["type"] = demangle(typeid(m_value).name());
    return jsonVar;
  }

private:
  friend class MainWindow;

  t m_value;
};