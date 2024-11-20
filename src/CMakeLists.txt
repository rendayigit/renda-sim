cmake_minimum_required(VERSION 3.21)
project(app LANGUAGES CXX)

# Set target directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

# Include SourceFiles.cmake to access the SOURCEFILES and INCLUDEDIRS variables
include(${CMAKE_SOURCE_DIR}/src/SourceFiles.cmake)

find_package(Boost 1.74.0 COMPONENTS filesystem REQUIRED)

add_definitions(-DBOOST_BIND_GLOBAL_PLACEHOLDERS)

add_executable(app ${SOURCEFILES})

target_link_libraries(app PRIVATE 
    Boost::filesystem
)

target_include_directories(app PUBLIC ${INCLUDEDIRS}
    ${CMAKE_SOURCE_DIR}/src/
)