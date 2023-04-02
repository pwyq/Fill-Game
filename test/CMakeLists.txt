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

file(GLOB TEST_SOURCES *.h)
file(GLOB OTHER_TEST_SOURCES other_tests/*.cpp)

add_executable(${BINARY_NAME} ${TEST_SOURCES} test_main.cpp)
add_executable(experiments experiments.cpp)
add_executable(other_tests ${OTHER_TEST_SOURCES})

target_link_libraries(${BINARY_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib GTest::gtest_main)
target_link_libraries(experiments PUBLIC ${CMAKE_PROJECT_NAME}_lib)
target_link_libraries(other_tests PUBLIC ${CMAKE_PROJECT_NAME}_lib)

add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
