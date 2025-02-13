#pragma once

#include <functional>
#include <stdexcept>
#include <vector>

/**
 * Forward declarations
 */
template <class T> class DataFlow;  // NOLINT(readability-identifier-naming)
template <class T> class InFlow;    // NOLINT(readability-identifier-naming)
template <class T> class OutFlow;   // NOLINT(readability-identifier-naming)
template <class T> class MuxInFlow; // NOLINT(readability-identifier-naming)
template <class T> class SumInFlow; // NOLINT(readability-identifier-naming)

/**
 * Base DataFlow class that allows the flow of data between models.
 */
template <class T> class DataFlow { // NOLINT(readability-identifier-naming)
public:
  /**
   * Constructors
   */
  DataFlow() = default;
  explicit DataFlow(T /*defaultValue*/);

  /**
   * Get the current value of the dataFlow variable.
   *
   * @return The current value.
   *
   * @throws None
   */
  T getValue() const { return m_currentValue; }

protected:
  /**
   * The current value of the dataFlow variable.
   */
  T m_currentValue;
};

/**
 * InFlow class that acts as an input dataFlow variable.
 */
template <class T> class InFlow : public DataFlow<T> { // NOLINT(readability-identifier-naming)
  friend class OutFlow<T>;

public:
  /**
   * Constructors
   */
  InFlow() : m_updateFunction([this](T t) { defaultUpdateFunction(t); }), m_isConnected(false) {}

  explicit InFlow(T defaultValue) : m_updateFunction([this](T t) { defaultUpdateFunction(t); }), m_isConnected(false) {
    this->m_currentValue = defaultValue;
  }

  /**
   * Sets the update callback function of the inFlow variable. This callback function is called when
   * the dataFlow variable is updated.
   *
   * @param updateFunction The function to be set as the event callback function.
   *
   * @throws None
   */
  void setUpdateFunction(std::function<void(T t)> updateFunction) { m_updateFunction = std::move(updateFunction); }

  /**
   * Set the current value of the dataFlow variable, then call the update function.
   *
   * @param t The new value.
   *
   * @throws None
   */
  virtual void setValue(T t) {
    this->m_currentValue = t;
    m_updateFunction(t);
  }

private:
  void setConnected() { m_isConnected = true; }
  bool getConnected() { return m_isConnected; }

  bool m_isConnected;

  std::function<void(T)> m_updateFunction;

  void defaultUpdateFunction(T t) {}
};

/**
 * SumInFlow class that sums the values of all connected OutFlows.
 */
template <class T> class SumInFlow : public InFlow<T> { // NOLINT(readability-identifier-naming)
public:
  /**
   * Constructors
   */
  SumInFlow() = default;
  explicit SumInFlow(T defaultValue) : InFlow<T>(defaultValue) {}

  /**
   * Override the setValue function to check if the value is 0.
   *
   * @param t The new value.
   *
   * @throws None
   */
  void setValue(T t) override {
    // if any outflow is connected , all outflow are summed.
    if (!this->connectedOutFlows.empty()) {
      t = {};
      for (const auto &connectedOutFlow : this->connectedOutFlows) {
        t += connectedOutFlow->getValue();
      }
    }
    // if outflow is not connected , SumInflow used like base inflow
    InFlow<T>::setValue(t);
  }

  std::vector<OutFlow<T> *> connectedOutFlows;
};

/**
 * OutFlow class that acts as an output dataFlow variable.
 */
template <class T> class OutFlow : public DataFlow<T> { // NOLINT(readability-identifier-naming)
public:
  /**
   * Constructors
   */
  OutFlow() : m_connectedInFlows({}) {}
  explicit OutFlow(T defaultValue) : m_connectedInFlows({}) { this->m_currentValue = defaultValue; }

  /**
   * Connect an inFlow variable to this outFlow variable.
   *
   * @param inFlow The inFlow variable to be connected.
   *
   * @throws std::invalid_argument exception is thrown when the provided 'inFlow' pointer is
   * nullptr, as it cannot be connected in that state.
   * @throws  std::logic_error exception will be thrown if the supplied 'inFlow' variable is
   * already linked to another outflow but not an instance of MuxInFlow<T>, since a regular InFlow
   * object can only support one output connection at any given time.
   * @throws  std::logic_error exception may arise when attempting to connect this same 'inFlow'
   * instance more than once, preventing redundant connections and potential issues in data
   * handling.
   */
  void connect(InFlow<T> *inFlow) {
    auto sumInFlow = dynamic_cast<SumInFlow<T> *>(inFlow);

    if (inFlow == nullptr) {
      throw std::invalid_argument("inflow is nullptr");
    }

    for (auto &connectedInFlow : m_connectedInFlows) {
      if (inFlow == connectedInFlow) {
        throw std::logic_error("inflow is already connected");
      }
    }

    if (sumInFlow) {
      sumInFlow->connectedOutFlows.push_back(this);
    } else {
      if (inFlow->getConnected()) {
        throw std ::logic_error("inflow is connected to another outflow");
      }
    }

    m_connectedInFlows.push_back(inFlow);
    inFlow->setConnected();
  }

  /**
   * Set the current value of the dataFlow variable. All the connected inFlow variables will be
   * automatically updated.
   *
   * @param t The new value.
   *
   * @throws None
   */
  void setValue(T t) {
    this->m_currentValue = t;

    for (auto &connectedInFlow : m_connectedInFlows) {
      connectedInFlow->setValue(t);
    }
  }

private:
  /**
   * The connected inFlow variables.
   */
  std::vector<InFlow<T> *> m_connectedInFlows;

  friend void InFlow<T>::setConnected();
  friend bool InFlow<T>::getConnected();
};