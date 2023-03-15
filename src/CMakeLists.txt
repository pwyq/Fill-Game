# ##
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:37:08
# @modify date 2023-03-15 10:29:13
# @desc cmake file for src/
# ##

# https://doc.qt.io/qt-5/cmake-get-started.html
# https://stackoverflow.com/questions/19761767/qt-5-cmake-fails-with-undefined-reference-to-vtable-on-hello-world-with-inc-sr

message(STATUS "hello????? from src/cmakelists")

# set the application name
set(BINARY_NAME ${CMAKE_PROJECT_NAME})

# solve missing headers
include_directories(${FILLGAME_HEADER_DIR})

if(IS_BUILD_GUI)
  file(GLOB_RECURSE GUI_SOURCE LIST_DIRECTORIES FALSE gui/*.cpp)
  file(GLOB_RECURSE GUI_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/gui/*.h)
endif()

# C++ implementations
# file(GLOB_RECURSE GUI_SOURCE LIST_DIRECTORIES FALSE gui/*.cpp)
file(GLOB_RECURSE SOLVER_SOURCE LIST_DIRECTORIES FALSE solver/*.cpp)

# file(GLOB_RECURSE GUI_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/gui/*.h)
file(GLOB_RECURSE SOLVER_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/solver/*.h)

# message(STATUS "debug = " ${GUI_SOURCE} ${GUI_HEADER})
if(IS_BUILD_GUI)
  # remove solver/fillgame.cpp; otherwise we will have two entry points (int main())
  # list(REMOVE_ITEM SOLVER_SOURCE ${FILLGAME_PROJ_DIR}/src/solver/fillgame.cpp)

  # only wrap GUI related headers
  qt5_wrap_cpp(GUI_HEADER_MOC ${GUI_HEADER})
  add_executable(${BINARY_NAME}_gui
    gui_main.cpp
    ${GUI_SOURCE}
    ${SOLVER_SOURCE}

    # ${SOLVER_HEADER}
    ${GUI_HEADER_MOC}
    ${FILLGAME_PROJ_DIR}/fillgame.qrc
  )
  add_library(${BINARY_NAME}_lib SHARED ${SOLVER_SOURCE} ${SOLVER_HEADER})

  # Add the Qt libraries for linking
  # qt5_use_modules(${BINARY_NAME} Widgets Gui Core)    # this is the same as the `target_link_libraries`; we only need one of them
  target_link_libraries(${BINARY_NAME}_gui
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core
  )
else()
  message(${SOLVER_SOURCE})
  message(${SOLVER_HEADER})
  add_executable(${BINARY_NAME}_cli
    # ${FILLGAME_PROJ_DIR}/src/solver/fillgame.cpp
    solver_main.cpp
    ${SOLVER_SOURCE}
  )
  add_library(${BINARY_NAME}_lib SHARED ${SOLVER_SOURCE} ${SOLVER_HEADER})
endif()

# add_library(${BINARY_NAME}_lib SHARED ${SOLVER_SOURCE} ${SOLVER_HEADER})

# # Add the Qt libraries for linking
# # qt5_use_modules(${BINARY_NAME} Widgets Gui Core)    # this is the same as the `target_link_libraries`; we only need one of them
# target_link_libraries(${BINARY_NAME}_gui
# PUBLIC
# Qt${QT_VERSION_MAJOR}::Widgets
# Qt${QT_VERSION_MAJOR}::Gui
# Qt${QT_VERSION_MAJOR}::Core
# )
