cmake_minimum_required(VERSION 3.10)
project(bug_sense_ui)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files
include_directories(include)

# Gather all source files
file(GLOB SOURCES "src/*.cpp")

# Create the executable
add_executable(bug_sense_ui ${SOURCES})