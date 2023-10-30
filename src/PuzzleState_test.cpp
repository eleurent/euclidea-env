#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "PuzzleState.h"

TEST(PuzzleStateTest, DrawLineTest) {
    Point A(0, 0), B(2, 0), C(1, 1), D(1, -1);
    Point E(1, 0);
    Point F(0, 1), G(2, -1);

    PuzzleState state({A, B, C, D, F, G}, {}, {}, {});
    state.drawLine(A, B);
    ASSERT_EQ(state.points.size(), 6);
    ASSERT_EQ(state.lines.size(), 1);
    ASSERT_EQ(state.circles.size(), 0);

    state.drawLine(C, D);
    ASSERT_EQ(state.points.size(), 7);
    ASSERT_EQ(state.lines.size(), 2);
    ASSERT_EQ(state.circles.size(), 0);
    EXPECT_THAT(state.points, ::testing::Contains(E));

    state.drawLine(F, G);
    ASSERT_EQ(state.points.size(), 7);
    ASSERT_EQ(state.lines.size(), 3);
    ASSERT_EQ(state.circles.size(), 0);

    state.drawLine(A, B);
    state.drawLine(C, D);
    ASSERT_EQ(state.points.size(), 7);
    ASSERT_EQ(state.lines.size(), 3);
    ASSERT_EQ(state.circles.size(), 0);
}

TEST(PuzzleStateTest, DrawCircleTest) {
    Point A(0, 0), B(1, 0);
    PuzzleState state({A, B}, {}, {}, {});
    
    state.drawCircle(A, B);
    ASSERT_EQ(state.points.size(), 2);
    ASSERT_EQ(state.lines.size(), 0);
    ASSERT_EQ(state.circles.size(), 1);
    
    state.drawCircle(B, A);
    ASSERT_EQ(state.points.size(), 4);
    ASSERT_EQ(state.lines.size(), 0);
    ASSERT_EQ(state.circles.size(), 2);
}

TEST(PuzzleStateTest, DrawLineCircleTest) {
    Point A(0, 0), B(1, 0), C(2, 0), D(2, 1);
    PuzzleState state({A, B, C}, {}, {Line(C, D)}, {PuzzleState::createCircle(A, B)});
    ASSERT_EQ(state.points.size(), 3);
    ASSERT_EQ(state.lines.size(), 1);
    ASSERT_EQ(state.circles.size(), 1);
    
    state.drawCircle(C, B);
    ASSERT_EQ(state.points.size(), 5);
    ASSERT_EQ(state.lines.size(), 1);
    ASSERT_EQ(state.circles.size(), 2);
    
    state.drawCircle(C, A);
    ASSERT_EQ(state.points.size(), 9);
    ASSERT_EQ(state.lines.size(), 1);
    ASSERT_EQ(state.circles.size(), 3);
    
    state.drawLine(A, D);
    ASSERT_EQ(state.points.size(), 14);
    ASSERT_EQ(state.lines.size(), 2);
    ASSERT_EQ(state.circles.size(), 3);
}