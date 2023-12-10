#pragma once

#include "PuzzleState.h"
#include <algorithm>

class Puzzle {
public:
    struct Action {
        enum ActionType { DrawLine, DrawCircle };
        ActionType type;
        Point p1, p2;
        Action(ActionType type, Point p1, Point p2) : type(type), p1(p1), p2(p2) {}
        bool Action::operator==(const Action& other) const;
    };

    Puzzle(
        const PuzzleState& initialState,
        const PuzzleState& goalState,
        const int optimalDepth
    ) : state(initialState), goalState(goalState), depth(0), optimalDepth(optimalDepth), enableRandomPoints(false) {}
    float cost() const;
    std::vector<Action> availableActions() const;
    Puzzle applyAction(const Action& action) const;

    PuzzleState state;
    int depth;
    int optimalDepth;
    bool enableRandomPoints;
    std::vector<Action::ActionType> actionsClue;
private:
    PuzzleState goalState;
};

Puzzle alpha0_equilateral_triangle();
Puzzle alpha2_mediator();
Puzzle alpha3_midpoint();
Puzzle alpha4_circle_in_square();
Puzzle alpha5_diamond_in_rectangle();
Puzzle alpha6_circle_centre();
Puzzle alpha7_inscribed_square();
Puzzle beta1_bisector();
Puzzle beta2_bisectors_centre();
Puzzle beta3_30deg_angle();
Puzzle beta8_tangent_to_line_at_point();
Puzzle gamma8_diamond();
Puzzle delta4_equilateral_triangle_in_circle();
Puzzle delta8_15deg_angle();