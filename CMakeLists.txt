cmake_minimum_required(VERSION 3.10)

project(euclidea-env)

find_package(CGAL CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(euclidea-env src/main.cpp src/PuzzleState.cpp src/Puzzle.cpp src/Search.cpp src/utils.cpp)
target_link_libraries(euclidea-env PRIVATE CGAL::CGAL)

enable_testing()
find_package(GTest 1.14.0 CONFIG REQUIRED)
include(GoogleTest)
add_executable(euclidea-test src/PuzzleState.cpp src/Puzzle.cpp src/utils.cpp src/PuzzleState_test.cpp src/Puzzle_test.cpp)
target_link_libraries(euclidea-test PRIVATE GTest::gtest_main CGAL::CGAL)
gtest_add_tests(TARGET euclidea-test TEST_PREFIX old:)
gtest_discover_tests(euclidea-test TEST_PREFIX new:)
