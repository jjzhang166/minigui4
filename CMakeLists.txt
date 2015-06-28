cmake_minimum_required(VERSION 3.0)
project(MINIGUI)

# 
# Versioning
# 

set(MINIGUI_MAJOR_VERSION 0)
set(MINIGUI_MINOR_VERSION 1)
set(MINIGUI_PATCH_VERSION 0)
set(MINIGUI_VERSION 
	"${MINIGUI_MAJOR_VERSION}.${MINIGUI_MINOR_VERSION}.${MINIGUI_PATCH_VERSION}")

# 
# Paths
# 

set(MINIGUI_LIB_DIR "${PROJECT_SOURCE_DIR}\\build\\${MINIGUI_VERSION}\\lib")
set(MINIGUI_BIN_DIR "${PROJECT_SOURCE_DIR}\\build\\${MINIGUI_VERSION}\\bin")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${MINIGUI_BIN_DIR})
set(CMAKE_SHARED_OUTPUT_DIRECTORY ${MINIGUI_BIN_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${MINIGUI_LIB_DIR})

# 
# Visual studio
# 

include(macros.cmake)
configure_msvc_runtime()

# 
# Boost
# 

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.57.0)
if (NOT Boost_FOUND)
	message("ERROR: Boost library not found")
	return()
endif()

# 
# Include
# 

include_directories(
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_BINARY_DIR}"
	"${Boost_INCLUDE_DIRS}")

# 
# Projects
# 

add_subdirectory(fastlz)
add_subdirectory(minigui)
add_subdirectory(miniguide)