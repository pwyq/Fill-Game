# ##
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:37:39
# @modify date 2023-03-15 13:25:44
# @desc This is the top-level CMakeLists.txt
# ##

cmake_minimum_required(VERSION 3.10)

# Set the project name and application name
project(fillgame VERSION 0.1.0 LANGUAGES CXX)

# IMPORTANT: set if to build with Qt GUI or not! Whenever switched the choice; do `rm -rf build/`
option(IS_BUILD_GUI "to build with Qt GUI or not" OFF)

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
add_subdirectory(lib/googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wreorder")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# # Turn on automatic invocation of the MOC, UIC & RCC
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# # There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# # a foolproof way to do it yet, so settle for the default error message for now.
# if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
# message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
# "environment variable to the install prefix of Qt 5, either on the command line as "
# "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
# endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# # Find the QtWidgets library
# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
set(FILLGAME_PROJ_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FILLGAME_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# sub directory's CMakeLists.txt
add_subdirectory(src)
add_subdirectory(test)
