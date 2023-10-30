#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math.h>
#include "Puzzle.h"

TEST(Puzzle, StepPuzzle) {
    Puzzle& puzzle = alpha0_equilateral_triangle();
    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 2);
    Puzzle& newPuzzle = puzzle.applyAction(actions[0]);
    ASSERT_NE(puzzle.state.points, newPuzzle.state.points);
}


TEST(PuzzleSolutions, Alpha0Test) {
    Puzzle& puzzle = alpha0_equilateral_triangle();
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


TEST(PuzzleSolutions, Alpha4Test) {
    Puzzle& puzzle = alpha4_circle_in_square();
    ASSERT_EQ(puzzle.cost(), 6);
    

    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 10);  // eight circles, two lines

    Point A(0, 0), B(1, 0), C(1, 1), D(0, 1);

    Puzzle::Action action1(Puzzle::Action::ActionType::DrawCircle, B, C);
    ASSERT_THAT(actions, ::testing::Contains(action1));
    puzzle = puzzle.applyAction(action1);
    ASSERT_EQ(puzzle.cost(), 6);

    Puzzle::Action action2(Puzzle::Action::ActionType::DrawCircle, B, C);
    ASSERT_THAT(actions, ::testing::Contains(action2));
    puzzle = puzzle.applyAction(action2);
    ASSERT_EQ(puzzle.cost(), 6);

    Point E(0, 0.5), F(1, 0.5);
    Puzzle::Action action3(Puzzle::Action::ActionType::DrawLine, E, F);
    ASSERT_THAT(actions, ::testing::Contains(action3));
    puzzle = puzzle.applyAction(action3);
    ASSERT_EQ(puzzle.cost(), 4);

    Puzzle::Action action4(Puzzle::Action::ActionType::DrawLine, A, C);
    ASSERT_THAT(actions, ::testing::Contains(action4));
    puzzle = puzzle.applyAction(action4);
    ASSERT_EQ(puzzle.cost(), 3);

    Point G(0.5, 0.5);
    Puzzle::Action action5(Puzzle::Action::ActionType::DrawCircle, G, F);
    ASSERT_THAT(actions, ::testing::Contains(action5));
    puzzle = puzzle.applyAction(action5);
    ASSERT_EQ(puzzle.cost(), 0);
}