cmake_minimum_required(VERSION 3.21)
project(renda-sim-engine LANGUAGES CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/)

# Include SourceFiles.cmake to access the SOURCEFILES and INCLUDEDIRS variables
include(${CMAKE_CURRENT_LIST_DIR}/SourceFiles.cmake)

find_package(
  Boost 1.74.0
  COMPONENTS filesystem
  REQUIRED)
find_package(spdlog REQUIRED)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_library(renda-sim-engine STATIC ${SOURCEFILES})

target_link_libraries(renda-sim-engine PRIVATE Boost::filesystem zmq
                                               spdlog::spdlog)

target_include_directories(renda-sim-engine PUBLIC ${INCLUDEDIRS})
