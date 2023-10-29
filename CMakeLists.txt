cmake_minimum_required(VERSION 3.10)

project(euclidea-env)

find_package(CGAL CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_executable(euclidea-env src/main.cpp src/PuzzleState.cpp)
target_link_libraries(euclidea-env PRIVATE CGAL::CGAL)

enable_testing()
find_package(GTest 1.14.0 CONFIG REQUIRED)
include(GoogleTest)

add_executable(PuzzleState_test src/PuzzleState_test.cpp)

target_link_libraries(PuzzleState_test PRIVATE GTest::gtest_main)
gtest_add_tests(TARGET PuzzleState_test TEST_PREFIX old:)
gtest_discover_tests(PuzzleState_test TEST_PREFIX new:)
# add_test(NAME monolithic COMMAND PuzzleState_test)