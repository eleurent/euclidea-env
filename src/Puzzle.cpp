#include "Puzzle.h"
#include "PuzzleState.h"

const float MIN_DISTANCE = 0.01f;


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
        if (std::find(state.lines.begin(), state.lines.end(), goalLine) == state.lines.end() &&
            std::find(state.lines.begin(), state.lines.end(), goalLine.opposite()) == state.lines.end()) {
            missingParts++;
        }
    }

    // Check missing circles
    for (const auto& goalCircle : goalState.circles) {
        if (std::find(state.circles.begin(), state.circles.end(), goalCircle) == state.circles.end() &&
            std::find(state.circles.begin(), state.circles.end(), goalCircle.opposite()) == state.circles.end()) {
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
            if (CGAL::squared_distance(state.points[i], state.points[j]) < MIN_DISTANCE)
                continue;
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
            if (CGAL::squared_distance(p1, p2) < MIN_DISTANCE)
                continue;
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

Puzzle Puzzle::applyAction(const Action& action) const {
    Puzzle puzzle(*this);
    switch (action.type) {
        case Action::DrawLine:
            puzzle.state.drawLine(action.p1, action.p2);
            break;
        case Action::DrawCircle:
            puzzle.state.drawCircle(action.p1, action.p2);
            break;
    }
    return puzzle;
}

Puzzle alpha0_equilateral_triangle() {
    Point A(0, 0), B(1, 0);
    PuzzleState initialState({A, B}, {Line(A, B)}, {});

    PuzzleState tmp = initialState;
    tmp.drawCircle(A, B);
    tmp.drawCircle(B, A);
    Point C = tmp.points.back();

    PuzzleState goalState({C}, {Line(A, C), Line(B, C)}, {});
    return Puzzle(initialState, goalState);
}

Puzzle alpha2_mediator() {
    Point A(0, 0), B(1, 0);
    PuzzleState initialState({A, B}, {Line(A, B)}, {});
    Point C(0.5, -1), D(0.5, 1);

    PuzzleState goalState({}, {Line(C, D)}, {});
    return Puzzle(initialState, goalState);
}

Puzzle alpha3_midpoint() {
    Point A(0, 0), B(1, 0);
    PuzzleState initialState({A, B}, {}, {});
    Point C(0.5, 0);
    PuzzleState goalState({C}, {}, {});
    return Puzzle(initialState, goalState);
}

Puzzle alpha4_circle_in_square() {
    Point A(0, 0), B(1, 0), C(1, 1), D(0, 1);
    PuzzleState initialState({A, B, C, D}, {Line(A, B), Line(B, C), Line(C, D), Line(D, A)}, {});
    Point E(0.5, 0.5), F(1, 0,5);
    PuzzleState goalState({}, {}, {PuzzleState::createCircle(E, F)});
    return Puzzle(initialState, goalState);
}

Puzzle beta8_tangent_to_line_at_point() {
    Point A(0, 0), B(1, 0);
    Point C(0.6, 1.33), D(1.26, 0.58);
    PuzzleState initialState({A, B, C, D}, {}, {PuzzleState::createCircle(A, B)});
    Point E(1, 1);
    PuzzleState goalState({}, {Line(B, E)}, {});
    return Puzzle(initialState, goalState);
}