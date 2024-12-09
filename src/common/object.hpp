#pragma once

#include <string>
#include <utility>

class Object {
public:
  explicit Object(std::string name, std::string description, Object *parent)
      : m_name(std::move(name)), m_description(std::move(description)), m_parent(parent) {}

  virtual ~Object() = default;

  std::string getName() const { return m_name; }
  std::string getDescription() const { return m_description; }

  Object *getParent() const { return m_parent; }

private:
  std::string m_name;
  std::string m_description;

  Object *m_parent;
};