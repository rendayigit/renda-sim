#pragma once

#include "Smp/IEntryPoint.h"

#include <functional>

class EntryPoint : Smp::IEntryPoint {
public:
  explicit EntryPoint(const std::function<void()> &eventFunction) : m_eventFunction(eventFunction) {};

  void Execute() const override { m_eventFunction(); }

private:
  std::function<void()> m_eventFunction;
};
