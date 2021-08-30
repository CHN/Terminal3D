cmake_minimum_required(VERSION 3.10)

project(Terminal3D VERSION 0.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build/")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build/Libraries/")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Build/Binaries/")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_UNITY_BUILD False)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/Source")

set(UTILITY_MODULE_PATH "${SOURCE_DIR}/BuildSystem/CMake/")

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${UTILITY_MODULE_PATH})

set(PLATFORMS "Windows" "MacOS" "Unix")

if(WIN32)
	list(GET PLATFORMS 0 PLATFORM)
	set(CURRENT_PLATFORM ${PLATFORM})
elseif(APPLE)
	list(GET PLATFORMS 1 PLATFORM)
	set(CURRENT_PLATFORM ${PLATFORM})
elseif(UNIX)
	list(GET PLATFORMS 2 PLATFORM)
	set(CURRENT_PLATFORM ${PLATFORM})
endif()

include("create_target")

add_subdirectory(Source)

##### CONFIG #####

set(CONFIG_DIR "${SOURCE_DIR}/Config")

configure_file(${PROJECT_NAME}Config.h.in "${CONFIG_DIR}/Public/${PROJECT_NAME}Config.h")

##### GOOGLE TEST BEGIN #####

#add_subdirectory(GoogleTest)

##### GOOGLE TEST END #####