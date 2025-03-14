#pragma once

#include <string>
#include <vector>

#include "modelVariable.hpp"
#include "scheduler/Entrypoint.hpp"

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
  int integer;
  bool boolean;
};

class SampleModel : public Model {
public:
  SampleModel();
  void step(int stepTime);

private:
  EntryPoint *m_eventSlow;
  EntryPoint *m_eventFast;
  EntryPoint *m_eventFaster;
  EntryPoint *m_eventFastest;

  ModelVariable<double> m_doubleValue;
  ModelVariable<int> m_integerValue;
  ModelVariable<bool> m_booleanValue;
  ModelVariable<std::string> m_stringValue;

  std::vector<ModelVariable<int> *> m_arrayValue; // TODO(renda): improve array support

  ModelVariable<std::vector<int>> *m_modelVarVector;

  std::vector<SampleChildModel *> m_childModels;
  // ModelVariable<int[5]> m_cArrayModelVariable;
  // ModelVariable<SampleSturcture> *m_structureModelVariable;

  ModelVariable<unsigned int> m_uintValue;
};