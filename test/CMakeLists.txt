set(SRC_INCLUDE ${CMAKE_SOURCE_DIR}/include/solver)

include_directories(${SRC_INCLUDE})

set(BINARY test_main)

file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)

# set(SOURCES ${TEST_SOURCES})

add_executable(${BINARY} ${TEST_SOURCES})

target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME}_lib gtest)
add_test(NAME ${BINARY} COMMAND ${BINARY})
