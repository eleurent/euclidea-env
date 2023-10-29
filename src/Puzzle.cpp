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


std::vector<Puzzle::Action> Puzzle::availableActions() const {
    std::vector<Action> actions;
    std::vector<Line> addedLines;
    addedLines.assign(state.lines.begin(), state.lines.end());  
    for (int i = 0; i < state.points.size(); ++i) {
        for (int j = i + 1; j < state.points.size(); ++j) {
            Line line(state.points[i], state.points[j]);
            if (std::find(addedLines.begin(), addedLines.end(), line) == addedLines.end() &&
                std::find(addedLines.begin(), addedLines.end(), line.opposite()) == addedLines.end()) {
                actions.push_back({ Action::DrawLine, state.points[i], state.points[j] });
                addedLines.push_back(line);
            }
        }
    }
    std::vector<Circle> addedCircles;
    addedCircles.assign(state.circles.begin(), state.circles.end());  
    for (const Point& p1 : state.points) {
        for (const Point& p2 : state.points) {
            Circle& circle = PuzzleState::createCircle(p1, p2);
            if (std::find(addedCircles.begin(), addedCircles.end(), circle) == addedCircles.end() &&
                std::find(addedCircles.begin(), addedCircles.end(), circle.opposite()) == addedCircles.end() &&
                p1 != p2) {
                addedCircles.push_back(circle);
                actions.push_back({ Action::DrawCircle, p1, p2 });
            }
        }
    }
    return actions;
}

void Puzzle::applyAction(const Action& action) {
    switch (action.type) {
        case Action::DrawLine:
            state.drawLine(action.p1, action.p2);
            break;
        case Action::DrawCircle:
            state.drawCircle(action.p1, action.p2);
            break;
    }
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