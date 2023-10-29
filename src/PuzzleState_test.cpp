#include <gtest/gtest.h>
#include "PuzzleState.h"


TEST(PuzzleStateTest, DrawLineTest) {
    Point A(0, 0);
    Point B(2, 0);
    Point C(1, 1);
    Point D(1, -1);

    Point E(1, 0);


    PuzzleState state({A, B, C, D}, {}, {});
    state.drawLine(A, B);

    ASSERT_EQ(state.points.size(), 4);
    ASSERT_EQ(state.lines.size(), 1);
    ASSERT_EQ(state.circles.size(), 0);

    state.drawLine(C, D);

    ASSERT_EQ(state.points.size(), 5);
    ASSERT_EQ(state.lines.size(), 2);
    ASSERT_EQ(state.circles.size(), 0);
    ASSERT_EQ(state.points.back(), E);
}