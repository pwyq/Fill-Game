# ##
# @author      Yanqing Wu, Junwen Shen
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:38:11
# @modify date 2023-03-16 22:03:23
# @desc cmake file for test
# ##
enable_testing()
include_directories(${FILLGAME_HEADER_DIR}/solver)

set(BINARY_NAME test_main)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY_NAME} ${TEST_SOURCES})

target_link_libraries(${BINARY_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)
add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
