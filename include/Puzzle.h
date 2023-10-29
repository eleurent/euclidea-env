#pragma once

#include "PuzzleState.h"
#include <algorithm>

class Puzzle {
public:
    Puzzle(const PuzzleState& initialState, const PuzzleState& goalState) : state(initialState), goalState(goalState) {}
    int cost() const;

    
    struct Action {
        enum ActionType { DrawLine, DrawCircle };
        ActionType type;
        Point p1, p2;
    };

    std::vector<Action> availableActions() const;
    void applyAction(const Action& action);



    PuzzleState state;
private:
    PuzzleState goalState;
};

Puzzle alpha1();