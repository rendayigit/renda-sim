#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>

class Object {
public:
  explicit Object(std::string name, std::string description, Object *parent)
      : m_name(std::move(name)), m_description(std::move(description)), m_parent(parent) {}

  virtual ~Object() = default;

  std::string getName() const { return m_name; }
  std::string getDescription() const { return m_description; }
  std::string getPath() const { return (m_parent == nullptr) ? m_name : m_parent->getPath() + "." + m_name; }

  Object *getParent() const { return m_parent; }

  virtual nlohmann::json getJson() = 0;

private:
  std::string m_name;
  std::string m_description;

  Object *m_parent;
};