cmake_minimum_required(VERSION 3.22)

project(wxMathPlot LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../wxMathPlot/lib/)

add_library(wxMathPlot
    ${CMAKE_CURRENT_LIST_DIR}/../wxMathPlot/src/mathplot.cpp
)

target_compile_definitions(wxMathPlot PUBLIC _FILE_OFFSET_BITS=64 WXUSINGDLL __WXGTK__)

target_include_directories(wxMathPlot PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../wxMathPlot/include
    ${CMAKE_CURRENT_LIST_DIR}/../wxWidgets/include
    ${CMAKE_CURRENT_LIST_DIR}/../wxWidgets/lib/wx/include/gtk3-unicode-3.2)