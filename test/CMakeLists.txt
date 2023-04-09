# ##
# @author      Yanqing Wu, Junwen Shen
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-10 05:38:11
# @modify date 2023-04-08 21:22:10
# @desc cmake file for test
# ##
enable_testing()
include_directories(${FILLGAME_HEADER_DIR})

set(BINARY_NAME test_main)

file(GLOB TEST_SOURCES algorithms/*.h)

add_executable(${BINARY_NAME} ${TEST_SOURCES} test_main.cpp)
add_executable(experiments helper.h other_tests/experiments.cpp)
add_executable(agent_fight helper.h other_tests/agent_fight.cpp)
add_executable(twoD_vs_oneD other_tests/twoD_vs_oneD.cpp)

target_link_libraries(${BINARY_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)
target_link_libraries(experiments PUBLIC ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(agent_fight PUBLIC ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(twoD_vs_oneD PUBLIC ${CMAKE_PROJECT_NAME}_lib)

add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
