#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <math.h>
#include "Puzzle.h"

TEST(Puzzle, StepPuzzle) {
    Puzzle& puzzle = alpha0_equilateral_triangle();
    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 3);
    Puzzle& newPuzzle = puzzle.applyAction(actions[0]);
    ASSERT_NE(puzzle.state.lines, newPuzzle.state.lines);
}


TEST(Puzzle, HashPuzzleState) {
    Puzzle& puzzle0 = alpha0_equilateral_triangle();
    Point A(0, 0), B(1, 0), C(0.5, sqrt(3)/2);
    
    Puzzle::Action action1(Puzzle::Action::ActionType::DrawCircle, A, B);
    Puzzle::Action action2(Puzzle::Action::ActionType::DrawCircle, B, A);
    Puzzle& puzzle1 = puzzle0.applyAction(action1);
    Puzzle& puzzle2 = puzzle0.applyAction(action2);
    Puzzle& puzzle12 = puzzle1.applyAction(action2);
    Puzzle& puzzle21 = puzzle2.applyAction(action1);

    EXPECT_NE(std::hash<PuzzleState>()(puzzle0.state), std::hash<PuzzleState>()(puzzle1.state));
    EXPECT_NE(std::hash<PuzzleState>()(puzzle0.state), std::hash<PuzzleState>()(puzzle2.state));
    EXPECT_NE(std::hash<PuzzleState>()(puzzle1.state), std::hash<PuzzleState>()(puzzle2.state));
    EXPECT_NE(std::hash<PuzzleState>()(puzzle0.state), std::hash<PuzzleState>()(puzzle12.state));
    EXPECT_NE(std::hash<PuzzleState>()(puzzle1.state), std::hash<PuzzleState>()(puzzle12.state));
    EXPECT_NE(std::hash<PuzzleState>()(puzzle2.state), std::hash<PuzzleState>()(puzzle12.state));
    EXPECT_EQ(std::hash<PuzzleState>()(puzzle12.state), std::hash<PuzzleState>()(puzzle21.state));
}



TEST(PuzzleSolutions, Alpha0Test) {
    Puzzle& puzzle = alpha0_equilateral_triangle();
    Point A(0, 0), B(1, 0), C(0.5, sqrt(3)/2);
    ASSERT_EQ(puzzle.cost(), 2.5);

    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 3);  // two circles and a line

    // First circle
    puzzle.state.drawCircle(A, B);
    ASSERT_EQ(puzzle.state.points.size(), 2);
    ASSERT_EQ(puzzle.cost(), 2.5);
    actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 2); // one circles centered on B, one centered on D


    // Second circle
    puzzle.state.drawCircle(B, A);
    ASSERT_EQ(puzzle.state.points.size(), 4);
    ASSERT_THAT(puzzle.state.points, ::testing::Contains(C));
    ASSERT_EQ(puzzle.cost(), 1);

    // Line AC
    puzzle.state.drawLine(A, C);
    ASSERT_EQ(puzzle.cost(), 0.5);
    // Line BC
    puzzle.state.drawLine(B, C);
    ASSERT_EQ(puzzle.cost(), 0);
}


TEST(PuzzleSolutions, Alpha4Test) {
    Puzzle& puzzle = alpha4_circle_in_square();
    ASSERT_EQ(puzzle.cost(), 6);

    Point A(0, 0), B(1, 0), C(1, 1), D(0, 1);
    Puzzle::Action action1(Puzzle::Action::ActionType::DrawCircle, B, C);
    auto& actions = puzzle.availableActions();
    ASSERT_EQ(actions.size(), 14);  // eight circles, six lines
    ASSERT_THAT(actions, ::testing::Contains(action1));
    puzzle = puzzle.applyAction(action1);
    ASSERT_EQ(puzzle.cost(), 6);

    Puzzle::Action action2(Puzzle::Action::ActionType::DrawCircle, C, B);
    actions = puzzle.availableActions();
    ASSERT_THAT(actions, ::testing::Contains(action2));
    puzzle = puzzle.applyAction(action2);
    ASSERT_EQ(puzzle.cost(), 6);

    Point E(0, 0.5), F(1, 0.5);
    Puzzle::Action action3(Puzzle::Action::ActionType::DrawLine, E, F);
    actions = puzzle.availableActions();
    ASSERT_THAT(actions, ::testing::Contains(action3));
    puzzle = puzzle.applyAction(action3);
    ASSERT_EQ(puzzle.cost(), 4);

    Puzzle::Action action4(Puzzle::Action::ActionType::DrawLine, A, C);
    actions = puzzle.availableActions();
    ASSERT_THAT(actions, ::testing::Contains(action4));
    puzzle = puzzle.applyAction(action4);
    ASSERT_EQ(puzzle.cost(), 2.75);  // Bonus because we have the circle center

    Point G(0.5, 0.5);
    ASSERT_THAT(puzzle.state.points, ::testing::Contains(G));
    ASSERT_THAT(puzzle.state.points, ::testing::Contains(F));
    Puzzle::Action action5(Puzzle::Action::ActionType::DrawCircle, G, F);
    actions = puzzle.availableActions();
    ASSERT_THAT(actions, ::testing::Contains(action5));
    puzzle = puzzle.applyAction(action5);
    ASSERT_EQ(puzzle.cost(), 0);
}


TEST(PuzzleSolutions, Beta8Test) {
    Puzzle& puzzle = beta8_tangent_to_line_at_point();
    ASSERT_EQ(puzzle.cost(), 0.75);

    auto& actions = puzzle.availableActions();
    for (auto& action: actions) {
        if ((action.type == Puzzle::Action::ActionType::DrawCircle) && action.p1.y() < -0.5 && action.p2.x() > 0.9) {
            puzzle = puzzle.applyAction(action);
            break;
        }
    }
    ASSERT_EQ(puzzle.cost(), 0.75);
    actions = puzzle.availableActions();
    for (auto& action: actions) {
        if ((action.type == Puzzle::Action::ActionType::DrawCircle) && action.p1.x() > 0.9 && action.p2.x() < -0.1) {
            puzzle = puzzle.applyAction(action);
            break;
        }
    }
    for (auto point: puzzle.state.points)
        std::cout << point << std::endl;
    ASSERT_EQ(puzzle.cost(), 0.5);


}
