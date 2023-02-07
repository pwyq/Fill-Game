# # https://doc.qt.io/qt-5/cmake-get-started.html
# # https://stackoverflow.com/questions/19761767/qt-5-cmake-fails-with-undefined-reference-to-vtable-on-hello-world-with-inc-sr




# set the application name
set(BINARY_NAME ${CMAKE_PROJECT_NAME})

# # C++ header files
# # set(SRC_INCLUDE ${CMAKE_SOURCE_DIR}/include)
# # include_directories(${SRC_INCLUDE})
# include_directories(${FILLGAME_HEADER_DIR})

# # C++ implementations
# file(GLOB_RECURSE SOURCES LIST_DIRECTORIES FALSE *.cpp)
# set(SOURCES ${SOURCES})


# # build the application
# add_executable(${BINARY_NAME}
#     ${SOURCES}
#     ${GUI_HEADER_MOC}
# )
# # qt5_use_modules(${BINARY_NAME} Widgets)
# message(STATUS "SOURCES include dir: ${SOURCES}\n") # debug
# message(STATUS "SRC_INCLUDE include dir: ${SRC_INCLUDE}\n") # debug
# add_library(${BINARY_NAME}_lib SHARED ${SOURCES})


# message(STATUS "QT_VERSION_MAJOR : ${QT_VERSION_MAJOR}\n") # debug

# # target_include_directories(${BINARY_NAME}
# #     PUBLIC
# #     ${Qt5Widgets_INCLUDE_DIRS}
# #     /usr/include/x86_64-linux-gnu/qt5/QtWidgets
# # )




# solve missing headers
include_directories(${FILLGAME_HEADER_DIR})

# C++ implementations
file(GLOB_RECURSE GUI_SOURCE LIST_DIRECTORIES FALSE gui/*.cpp)
set(GUI_SOURCE ${GUI_SOURCE})
file(GLOB_RECURSE SOLVER_SOURCE LIST_DIRECTORIES FALSE solver/*.cpp)
set(SOLVER_SOURCE ${SOLVER_SOURCE})

file(GLOB_RECURSE GUI_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/gui/*.h)
file(GLOB_RECURSE SOLVER_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/solver/*.h)
set(GUI_HEADER ${GUI_HEADER})
set(SOLVER_HEADER ${SOLVER_HEADER})

# message(STATUS "GUI_SOURCE : ${GUI_SOURCE}\n") # debug
# message(STATUS "GUI_HEADER : ${GUI_HEADER}\n") # debug

qt5_wrap_cpp(GUI_HEADER_MOC ${GUI_HEADER} ${SOLVER_HEADER})

add_executable(${BINARY_NAME}
    main.cpp
    ${GUI_SOURCE}
    ${SOLVER_SOURCE}
    ${GUI_HEADER_MOC}
)

# file(GLOB_RECURSE SOLVER_HEADER LIST_DIRECTORIES FALSE ${FILLGAME_HEADER_DIR}/solver/*.h)
# add_library(${BINARY_NAME}_lib SHARED ${SOLVER_SOURCE} ${SOLVER_HEADER} ${GUI_SOURCE} ${GUI_HEADER})
add_library(${BINARY_NAME}_lib SHARED ${SOLVER_SOURCE} ${SOLVER_HEADER})


# Add the Qt libraries for linking
# qt5_use_modules(${BINARY_NAME} Widgets Gui Core)    # this is the same as the `target_link_libraries`; we only need one of them
target_link_libraries(${BINARY_NAME}
    PUBLIC
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Core
)
