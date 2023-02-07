cmake_minimum_required(VERSION 3.10)
project(fillgame)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_GLIBCXX_DEBUG")
add_subdirectory(lib/googletest)
add_subdirectory(src/solver)
add_subdirectory(test)
