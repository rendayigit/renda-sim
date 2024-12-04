cmake_minimum_required(VERSION 3.21)
project(renda-sim LANGUAGES CXX)

# Set target directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/)

# Include SourceFiles.cmake to access the SOURCEFILES and INCLUDEDIRS variables
include(${CMAKE_CURRENT_LIST_DIR}/SourceFiles.cmake)

find_package(
  Boost 1.74.0
  COMPONENTS filesystem
  REQUIRED)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(renda-sim ${SOURCEFILES})

target_link_libraries(renda-sim PRIVATE
    Boost::filesystem)

target_include_directories(renda-sim PUBLIC ${INCLUDEDIRS})
