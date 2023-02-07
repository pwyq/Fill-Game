include_directories(${FILLGAME_HEADER_DIR}/solver)

set(BINARY_NAME test_main)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

add_executable(${BINARY_NAME} ${TEST_SOURCES})

target_link_libraries(${BINARY_NAME} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
add_test(NAME ${BINARY_NAME} COMMAND ${BINARY_NAME})
