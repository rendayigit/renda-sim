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

target_compile_definitions(renda-sim PUBLIC _FILE_OFFSET_BITS=64 WXUSINGDLL
                                            __WXGTK__)

target_link_libraries(renda-sim PRIVATE
    Boost::filesystem
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxWidgets/lib/libwx_baseu_net-3.2.so.0
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxWidgets/lib/libwx_baseu-3.2.so.0
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxWidgets/lib/libwx_gtk3u_core-3.2.so.0
    ${CMAKE_CURRENT_LIST_DIR}/../deps/wxMathPlot/lib/libwxMathPlot.a)

target_include_directories(renda-sim PUBLIC ${INCLUDEDIRS})
