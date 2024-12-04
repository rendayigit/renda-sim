cmake_minimum_required(VERSION 3.21)
project(tests LANGUAGES CXX)

# Enable coverage
if(${ENABLE_COVERAGE})
  message("#################### Coverage Enabled ####################")
  set(GCOV_LINK_FLAGS "--coverage -O0 -g")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCOV_LINK_FLAGS}")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCOV_LINK_FLAGS}")
endif()

# Set target directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../bin/)

# Include SourceFiles.cmake to access the SOURCEFILES and INCLUDEDIRS variables
include(${CMAKE_CURRENT_LIST_DIR}/TestFiles.cmake)

find_package(Boost 1.74.0 COMPONENTS filesystem REQUIRED)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(tests ${TESTFILES})

target_include_directories(tests PUBLIC ${INCLUDEDIRS})

target_link_libraries(tests PRIVATE 
    gtest_main
    gtest
    Boost::filesystem
    zmq
)

include(GoogleTest)
gtest_discover_tests(tests)