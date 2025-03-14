#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "model/object.hpp"

class Model : public Object {
public:
  explicit Model(std::string name, std::string description, Object *parent);

  std::vector<Object *> getChildren() const { return m_children; }

  nlohmann::json getModelTreeJson();

private:
  nlohmann::json getJson() override;

  template <typename t> friend class ModelVariable;

  void addChild(Object *child);

  std::vector<Object *> m_children;
};