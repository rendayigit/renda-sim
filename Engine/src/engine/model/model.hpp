#pragma once

#include <nlohmann/json.hpp>
#include <string>
#include <utility>
#include <vector>

#include "engine/model/object.hpp"

class Model : public Object {
public:
  explicit Model(std::string name, std::string description, Object *parent);

  std::vector<Object *> getChildren() const { return m_children; }

  nlohmann::json getModelTreeJson();

private:
  template <typename t> friend class ModelVariable;

  void addChild(Object *child);

  std::vector<Object *> m_children;
};