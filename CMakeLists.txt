cmake_minimum_required(VERSION 3.10)

# set the project name
project(Terminal3D)

# set the project name and version
project(Terminal3D VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/output/")

set(INCLUDES_DIR "${PROJECT_SOURCE_DIR}/includes/")
file(GLOB_RECURSE SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_UNITY_BUILD False)

# add the executable
add_executable(Terminal3D main.cpp)

target_include_directories(Terminal3D PUBLIC "${INCLUDES_DIR}")
target_sources(Terminal3D PRIVATE "${SOURCE_DIR}")

target_link_libraries(Terminal3D PUBLIC ncurses)

configure_file(Terminal3DConfig.h.in "${INCLUDES_DIR}/Terminal3DConfig.h")