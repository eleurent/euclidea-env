#include "Puzzle.h"
#include "PuzzleState.h"


int Puzzle::cost() const {
    int missingParts = 0;

    // Check missing points
    for (const auto& goalPoint : goalState.points) {
        if (std::find(state.points.begin(), state.points.end(), goalPoint) == state.points.end()) {
            missingParts++;
        }
    }

    // Check missing lines
    for (const auto& goalLine : goalState.lines) {
        if (std::find(state.lines.begin(), state.lines.end(), goalLine) == state.lines.end()) {
            missingParts++;
        }
    }

    // Check missing circles
    for (const auto& goalCircle : goalState.circles) {
        if (std::find(state.circles.begin(), state.circles.end(), goalCircle) == state.circles.end()) {
            missingParts++;
        }
    }

    return missingParts;
}

Puzzle alpha1() {
    Point A(0, 0), B(1, 0);
    PuzzleState initialState({A, B}, {Line(A, B)}, {});

    PuzzleState tmp = initialState;
    tmp.drawCircle(A, B);
    tmp.drawCircle(B, A);
    Point C = tmp.points.back();

    PuzzleState goalState({C}, {Line(A, C), Line(B, C)}, {});
    return Puzzle(initialState, goalState);
}