# ##
# @author      Yanqing Wu, Junwen Shen
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:37:39
# @modify date 2023-03-23 02:53:44
# @desc This is the top-level CMakeLists.txt
# ##

cmake_minimum_required(VERSION 3.10)

# Set the project name and application name
project(fillgame VERSION 0.1.0 LANGUAGES CXX)

# IMPORTANT: set if to build with Qt GUI or not! Whenever switched the choice; do `rm -rf build/`
option(IS_BUILD_GUI "to build with Qt GUI or not" OFF)

set(IS_BUILD_GUI ON)

if(IS_BUILD_GUI)
  message(STATUS "\nBuilding with Qt GUI...\n")

  # Turn on automatic invocation of the MOC, UIC & RCC
  set(CMAKE_AUTOMOC ON)
  set(CMAKE_AUTOUIC ON)
  set(CMAKE_AUTORCC ON)

  # Find the QtWidgets library
  find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
  find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
else()
  message(STATUS "\nBuilding without Qt GUI...\n")
endif()

# 3rd party; should be above our own settings
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG b796f7d44681514f58a683a3a71ff17c94edb0c1 # release-1.13.0
)

if(WIN32)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
endif()

FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
elseif(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreorder")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set directory variables for usage in child CMakeLists.txt
set(FILLGAME_PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FILLGAME_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# sub directory's CMakeLists.txt
add_subdirectory(src)
add_subdirectory(test)
