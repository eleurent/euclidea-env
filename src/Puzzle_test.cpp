#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math.h>
#include "Puzzle.h"

TEST(PuzzleSolutions, Alpha1Test) {
    Puzzle& puzzle = alpha1();
    ASSERT_EQ(puzzle.cost(), 3);
    Point C(0.5, sqrt(3)/2);

    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 2);  // two circles

    // First circle
    puzzle.state.drawCircle(puzzle.state.points[0], puzzle.state.points[1]);
    ASSERT_EQ(puzzle.cost(), 3);
    actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 4); // 2 circles centered on B, 2 centered on D


    // Second circle
    puzzle.state.drawCircle(puzzle.state.points[1], puzzle.state.points[0]);
    ASSERT_EQ(puzzle.state.points.size(), 6);
    ASSERT_THAT(puzzle.state.points, ::testing::Contains(C));
    ASSERT_EQ(puzzle.cost(), 2);

    // Line AC
    puzzle.state.drawLine(puzzle.state.points[0], C);
    ASSERT_EQ(puzzle.cost(), 1);
    // Line BC
    puzzle.state.drawLine(puzzle.state.points[1], C);
    ASSERT_EQ(puzzle.cost(), 0);
}
