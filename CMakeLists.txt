# This is the top-level CMakeLists.txt

cmake_minimum_required(VERSION 3.10)

# Set the project name and application name
project(fillgame VERSION 0.1.0 LANGUAGES CXX)

# 3rd party; should be above our own settings
add_subdirectory(lib/googletest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Turn on automatic invocation of the MOC, UIC & RCC
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTORCC ON)

# # Find includes in the build directories
# # https://askubuntu.com/questions/633826/default-installation-prefix-qt5-qt5-widgets-ubuntu
# # set(CMAKE_PREFIX_PATH /usr/lib/qt5)  # for Ubuntu, needs to find gcc_64
# # set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt5.12.8/5.12.8/gcc_64)  # for Ubuntu, needs to find gcc_64
# # set(CMAKE_PREFIX_PATH /usr/include/x86_64-linux-gnu/qt5)  # for Ubuntu, needs to find gcc_64

# if(CMAKE_VERSION VERSION_LESS "3.7.0")
#     set(CMAKE_INCLUDE_CURRENT_DIR ON)
# endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")

# # Make this a GUI application on Windows
# if(WIN32)
#   set(CMAKE_WIN32_EXECUTABLE ON)
# endif()

# # these variables are usable in the child CMakeLists
# set(FILLGAME_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
# # set(FILLGAME_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
# # include_directories(
#   # ${FILLGAME_HEADER_DIR}
#   # ${FILLGAME_SRC_DIR}
# # )

# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)
# # Add subdirectories; these will trigger CMakeLists.txt in the subdirectories
# add_subdirectory(src)
# add_subdirectory(test)



# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Turn on automatic invocation of the MOC, UIC & RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# There may be a way to tell up front if Qt5 is going to be found, but I haven't found
# a foolproof way to do it yet, so settle for the default error message for now.
if(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)
   message(WARNING "CMAKE_PREFIX_PATH is not defined, so find_package may not work. Set the CMAKE_PREFIX_PATH "
           "environment variable to the install prefix of Qt 5, either on the command line as "
           "-DCMAKE_PREFIX_PATH=\"path/to/Qt5/lib/cmake\" or with set(CMAKE_PREFIX_PATH path/to/Qt5/lib/cmake)")
endif(NOT CMAKE_PREFIX_PATH AND NOT Qt5Widgets_DIR)

# Add a compiler flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

# Make this a GUI application on Windows
if(WIN32)
  set(CMAKE_WIN32_EXECUTABLE ON)
endif()

# Find the QtWidgets library
find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Gui REQUIRED)


# Tell CMake to create the helloworld executable
#add_executable(helloworld main.cpp mainwindow.cpp mainwindow.ui resources.qrc)

# Add the Qt5 Widgets for linking
#target_link_libraries(helloworld Qt5::Widgets)

# set(QRC_FILE ${CMAKE_CURRENT_SOURCE_DIR}/resources.qrc)
# set(QRC_FILE resources.qrc)
# set(RES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources)
# set(HW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(FILLGAME_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_subdirectory(src)
add_subdirectory(test)

