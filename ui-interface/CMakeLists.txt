cmake_minimum_required(VERSION 3.10)
project(bug_sense_ui)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include header files
include_directories(include)

# Gather all source and includes
file(GLOB SOURCES "src/*.cpp" "include/*.h")

set(Qt5_DIR "C:/Qt/qt5-build/qtbase-install/lib/cmake/Qt5")

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

# Create the executable
add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
    Qt5::Widgets 
    Qt5::Charts
)
