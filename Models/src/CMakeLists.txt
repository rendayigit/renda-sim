cmake_minimum_required(VERSION 3.21)
project(renda-sim-models LANGUAGES CXX)

# Set target directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

# Include SourceFiles.cmake to access the SOURCEFILES and INCLUDEDIRS variables
include(${CMAKE_CURRENT_LIST_DIR}/SourceFiles.cmake)

find_package(
  Boost 1.74.0
  COMPONENTS filesystem
  REQUIRED)

find_package(spdlog REQUIRED)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(renda-sim-models ${SOURCEFILES})

target_link_libraries(
  renda-sim-models
  PRIVATE -L${CMAKE_SOURCE_DIR}/../Engine/lib/ -lrenda-sim-engine
          Boost::filesystem zmq spdlog::spdlog)

target_include_directories(renda-sim-models PUBLIC ${INCLUDEDIRS})
