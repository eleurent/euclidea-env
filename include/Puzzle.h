#pragma once

#include "PuzzleState.h"
#include <algorithm>

class Puzzle {
public:
    Puzzle(const PuzzleState& initialState, const PuzzleState& goalState) : state(initialState), goalState(goalState) {}
    int cost() const;

    PuzzleState state;
private:
    PuzzleState goalState;
};

Puzzle alpha1();