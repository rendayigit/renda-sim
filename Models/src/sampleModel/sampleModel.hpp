#pragma once

#include <nlohmann/adl_serializer.hpp>
#include <string>
#include <vector>

#include "modelVariable.hpp"
#include "simpleEvent.hpp"

class SampleGrandChildModel : public Model {
public:
  SampleGrandChildModel(const std::string &name, const std::string &description, Model *parent)
      : Model(name, description, parent), m_boolValue("Boolean Variable", "Sample Boolean Variable", this, false) {}

private:
  ModelVariable<bool> m_boolValue;
};

class SampleChildModel : public Model {
public:
  SampleChildModel(const std::string &name, const std::string &description, Model *parent)
      : Model(name, description, parent), m_integerValue("Integer Variable", "Sample Integer Variable", this, 1),
        m_sampleGrandChildModel("Sample Grand Child", "A sample grand child model", this) {}

private:
  ModelVariable<int> m_integerValue;
  SampleGrandChildModel m_sampleGrandChildModel;
};

struct SampleSturcture {
  int integer = 1;
  bool boolean = true;
  std::string string = "Default structure string";

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(SampleSturcture, integer, boolean, string)
};

// Specialization for serializing SampleSturcture*
namespace nlohmann {
template <> struct adl_serializer<SampleSturcture *> {
  static void to_json(json &j, const SampleSturcture *const &ptr) {
    if (ptr == nullptr) {
      j = nullptr; // Handle null pointer case
    } else {
      j = *ptr; // Delegate to the existing SampleSturcture serialization
    }
  }

  static void from_json(const json &j, SampleSturcture *&ptr) {
    if (j.is_null()) {
      ptr = nullptr;
    } else {
      if (ptr == nullptr) {
        ptr = new SampleSturcture();
      }
      *ptr = j.get<SampleSturcture>();
    }
  }
};
} // namespace nlohmann

class SampleModel : public Model {
public:
  SampleModel();
  void step(int stepTime);

private:
  SimpleEvent *m_eventSlow;
  SimpleEvent *m_eventFast;
  SimpleEvent *m_eventFaster;
  SimpleEvent *m_eventFastest;

  ModelVariable<double> m_doubleValue;
  ModelVariable<int> m_integerValue;
  ModelVariable<bool> m_booleanValue;
  ModelVariable<std::string> m_stringValue;

  std::vector<ModelVariable<int> *> m_arrayValue; // TODO(renda): improve array support

  ModelVariable<std::vector<int>> *m_modelVarVector;

  std::vector<SampleChildModel *> m_childModels;
  // ModelVariable<int[5]> m_cArrayModelVariable;
  ModelVariable<SampleSturcture *> m_structureModelVariable;

  ModelVariable<unsigned int> m_uintValue;
};