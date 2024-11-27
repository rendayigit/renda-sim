#pragma once

#include <string>
#include <utility>

class ModelItem {
public:
  explicit ModelItem(std::string name, std::string description)
      : m_name(std::move(name)), m_description(std::move(description)) {}

  std::string getName() const { return m_name; }
  std::string getDescription() const { return m_description; }

private:
  std::string m_name;
  std::string m_description;
};