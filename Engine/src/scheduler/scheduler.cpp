#include <chrono>
#include <fstream>
#include <memory>
#include <nlohmann/json.hpp>
#include <string>

#include "common.hpp"
#include "logger/logger.hpp"
#include "messaging/publisher.hpp"
#include "scheduler/Entrypoint.hpp"
#include "scheduler/scheduler.hpp"
#include "timer/timer.hpp"

constexpr int MICROS_TO_MILLIS = 1000;
constexpr int MILLIS_TO_SECS = 1000;
constexpr int LOGGER_RATE_MULTIPLIER = 100;

Scheduler::Scheduler() : m_work(m_ioService) {
  nlohmann::json config;

  std::ifstream configFile(CONFIG_PATH);
  if (not configFile.is_open()) {
    Logger::error("Could not open the config file: " + CONFIG_PATH);
  } else {
    try {
      configFile >> config;

      if (config.contains("SCHEDULER_STEP_TIME_MICROS") and config["SCHEDULER_STEP_TIME_MICROS"].is_number_float()) {
        m_stepTimeMicros = config["SCHEDULER_STEP_TIME_MICROS"].get<double>();
      } else {
        Logger::error("Key 'SCHEDULER_STEP_TIME_MICROS' not found or is not a float.");
      }

      if (config.contains("SCHEDULER_DEFAULT_RATE") and config["SCHEDULER_DEFAULT_RATE"].is_number_float()) {
        m_rate = config["SCHEDULER_DEFAULT_RATE"].get<double>();
      } else {
        Logger::error("Key 'SCHEDULER_DEFAULT_RATE' not found or is not a float.");
      }

    } catch (const nlohmann::json::parse_error &e) {
      Logger::critical("JSON parse error: " + std::string(e.what()));
    }
  }

  AddSimulationTimeEvent(new EntryPoint([&] { transmitTime(); }), 0, 100, -1);
}

Scheduler::~Scheduler() {
  stop();
  m_lastStopTicks = {};
  m_progressTimeLastMillis = {};

  m_ioService.stop();

  if (m_workingThread.joinable()) {
    m_workingThread.join();
  }

  m_entryPoints->clear();
}

void Scheduler::start() {
  if (m_lastStopTicks != 0) {
    Timer::getInstance().updateInitialTicks(m_lastStopTicks);
  }

  m_isRunning = true;
  Logger::info("Simulation started");

  setRate(m_rate);

  m_workingThread = std::thread([this]() { m_ioService.run(); });
}

void Scheduler::stop() {
  m_isRunning = false;

  Logger::info("Simulation stopped");

  if (m_schedulerThread.joinable()) {
    m_schedulerThread.join();
  }

  m_lastStopTicks = std::chrono::high_resolution_clock::now().time_since_epoch().count();

  // m_work.get_io_context().stop();
  if (m_workingThread.joinable()) {
    m_workingThread.join();
  }
}

void Scheduler::reset() {
  Timer::getInstance().reset();
  // TODO(renda): Reset all events and models
}

void Scheduler::setRate(double rate) { m_rate = rate; }

void Scheduler::progressTime(long millis) {
  m_progressTimeLastMillis += millis;
  // step(m_progressTimeLastMillis);
}

void Scheduler::handleEvent(EntryPoint *entryPoint, long simulationTime, long cycleTime, int repeat) {
  entryPoint->Execute();

  auto timer = std::make_unique<boost::asio::deadline_timer>(m_ioService);
  long nextCycleTime = static_cast<long>(cycleTime / m_rate);
  timer->expires_from_now(boost::posix_time::milliseconds(nextCycleTime));

  // Bind the event by reference to the lambda to ensure the current instance is captured.
  timer->async_wait([&](const boost::system::error_code &errorCode) {
    if (boost::asio::error::operation_aborted == errorCode) {
      // FIXME
      Logger::error("Operation aborted");
      return;
    } else {
      // FIXME
      Logger::error("Other error");
      return;
    }

    handleEvent(entryPoint, simulationTime, cycleTime, repeat);
  });
}

void Scheduler::AddSimulationTimeEvent(EntryPoint *entryPoint, long simulationTime, long cycleTime, int repeat) {
  // Ensure the entryPoint is not already added.
  if (std::find(m_entryPoints->begin(), m_entryPoints->end(), entryPoint) == m_entryPoints->end()) {
    // Insert entryPoint to entrypoint list
    m_entryPoints->push_back(entryPoint);
  } else {
    Logger::warn("Entrypoint already added.");
    return;
  }

  auto timer = std::make_unique<boost::asio::deadline_timer>(m_ioService);
  timer->expires_from_now(boost::posix_time::milliseconds(static_cast<int>(simulationTime / m_rate)));
  timer->async_wait([&](const boost::system::error_code &errorCode) {
    if (boost::asio::error::operation_aborted == errorCode) {
      // FIXME
      Logger::error("Operation aborted");
      return;
    } else {
      // FIXME
      Logger::error("Other error");
      return;
    }

    handleEvent(entryPoint, simulationTime, cycleTime, repeat);
  });
}

void Scheduler::transmitTime() {
  double simTimeInSeconds = static_cast<double>(Timer::getInstance().simMillis()) / MILLIS_TO_SECS;

  std::string simTimeStr = std::to_string(simTimeInSeconds);
  simTimeStr = simTimeStr.substr(0, simTimeStr.find('.') + 3); // Keep 2 decimal places

  nlohmann::json message;
  message["simTime"] = simTimeStr;
  message["missionTime"] = ""; // TODO: implement
  message["epochTime"] = "";   // TODO: implement
  message["zuluTime"] = "";    // TODO: implement

  Publisher::getInstance().queueMessage("TIME", message);
}
