#include "Puzzle.h"
#include "PuzzleState.h"
#include "utils.h"

const float MIN_DISTANCE = 0.01f;

bool Puzzle::Action::operator==(const Puzzle::Action& other) const {
    bool sameLine = ((type == other.type == DrawLine) && ((Line(p1, p2) == Line(other.p1, other.p2)) || (Line(p1, p2) == Line(other.p1, other.p2).opposite())));
    bool sameCircle = ((type == other.type == DrawCircle) && ((PuzzleState::createCircle(p1, p2) == PuzzleState::createCircle(other.p1, other.p2)) ||
                                                            (PuzzleState::createCircle(p1, p2) == PuzzleState::createCircle(other.p1, other.p2).opposite()))) ;
    return sameLine || sameCircle;
}

float Puzzle::cost() const {
    float cost = 0;

    // Check missing points
    for (const auto& goalPoint : goalState.points) {
        if (Utils::find(goalPoint, state.points)) {
            cost++;
        }
    }

    // Check missing lines
    for (const auto& goalLine : goalState.lines) {
        if (std::find(state.lines.begin(), state.lines.end(), goalLine) == state.lines.end() &&
            std::find(state.lines.begin(), state.lines.end(), goalLine.opposite()) == state.lines.end()) {
            cost++;

            // Add bonus for construction points (but not beyond 2 points)
            int numConstructionPoints = 0;
            for (const auto& point: state.points) {
                if (Utils::isOn(point, goalLine)) numConstructionPoints++;
            }
            cost -= 0.25f * std::min(numConstructionPoints, 2);
        }
    }

    // Check missing circles
    for (const auto& goalCircle : goalState.circles) {
        if (std::find(state.circles.begin(), state.circles.end(), goalCircle) == state.circles.end() &&
            std::find(state.circles.begin(), state.circles.end(), goalCircle.opposite()) == state.circles.end()) {
            cost++;

            // Add bonus for construction points: center
            if (Utils::find(goalCircle.center(), state.points))
                cost -= 0.25f;

            // A point on the circle
            for (const auto& point: state.points) {
                if (Utils::isOn(point, goalCircle)) {
                    cost -= 0.25f;
                    break;
                }
            }

        }
    }

    return cost;
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
    const PuzzleState initialState({A, B}, {Segment(A, B)}, {}, {});

    PuzzleState tmp = initialState;
    tmp.drawCircle(A, B);
    tmp.drawCircle(B, A);
    Point C = tmp.points.back();

    const PuzzleState goalState({C}, {}, {Line(A, C), Line(B, C)}, {});
    const int optimalDepth = 3;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha2_mediator() {
    Point A(0, 0), B(1, 0);
    const PuzzleState initialState({A, B}, {Segment(A, B)}, {}, {});
    Point C(0.5, -1), D(0.5, 1);

    const PuzzleState goalState({}, {}, {Line(C, D)}, {});
    const int optimalDepth = 3;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha3_midpoint() {
    Point A(0, 0), B(1, 0);
    const PuzzleState initialState({A, B}, {}, {}, {});
    Point C(0.5, 0);
    const PuzzleState goalState({C}, {}, {}, {});
    const int optimalDepth = 4;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha4_circle_in_square() {
    Point A(0, 0), B(1, 0), C(1, 1), D(0, 1);
    const PuzzleState initialState({A, B, C, D}, {Segment(A, B), Segment(B, C), Segment(C, D), Segment(D, A)}, {}, {});
    Point E(0.5, 0.5), F(1, 0.5), G(0, 0.5), H(0.5, 0), I(0.5, 1);
    const PuzzleState goalState({E, F, G, H, I}, {}, {}, {PuzzleState::createCircle(E, F)});
    const int optimalDepth = 5;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha5_diamond_in_rectangle() {
    Point A(0, 0), B(2, 0), C(2, 1), D(0, 1);
    const PuzzleState initialState({A, B, C, D}, {Segment(A, B), Segment(B, C), Segment(C, D), Segment(D, A)}, {}, {});
    
    PuzzleState tmp = initialState;
    tmp.drawCircle(A, C);
    tmp.drawCircle(C, A);
    Point E(tmp.points[tmp.points.size()-2]), F(tmp.points[tmp.points.size()-1]);
    tmp.drawLine(E, F);
    Point G(tmp.points[tmp.points.size()-2]), H(tmp.points[tmp.points.size()-1]);

    const PuzzleState goalState({G, H}, {}, {Line(A, G), Line(C, H)}, {});
    const int optimalDepth = 5;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha6_circle_centre() {
    Point A(0, 0), B(1, 0);
    const PuzzleState initialState({}, {}, {}, {PuzzleState::createCircle(A, B)});
    const PuzzleState goalState({A}, {}, {}, {});
    const int optimalDepth = 5;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle alpha7_inscribed_square() {
    Point A(0, 0), B(0, 1);
    const PuzzleState initialState({A, B}, {}, {}, {PuzzleState::createCircle(A, B)});
    Point C(1, 0), D(0, -1), E(-1, 0);
    const PuzzleState goalState({C, D, E}, {}, {Line(B, C), Line(C, D), Line(D, E), Line(E, B)}, {});
    const int optimalDepth = 7;
    return Puzzle(initialState, goalState, optimalDepth);
}


Puzzle beta1_bisector() {
    // TODO : requires addition of random points 
    Point A(0, 0), B(100, 0), C(100, 100);
    // We use segments instead of half-lines here
    const PuzzleState initialState({A}, {Segment(A, B), Segment(A, C)}, {}, {});
    
    PuzzleState tmp = initialState;
    tmp.drawCircle(A, Point(1, 0));
    Point E(tmp.points[tmp.points.size()-2]), F(tmp.points[tmp.points.size()-1]);
    tmp.drawCircle(E, F);
    tmp.drawCircle(F, E);
    Point H(tmp.points[tmp.points.size()-1]);

    const PuzzleState goalState({}, {}, {Line(A, H)}, {});
    const int optimalDepth = 4;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle beta2_bisectors_centre() {
    Point A(0, 0), B(2, 0), C(0.1, 1);
    // We use segments instead of half-lines here
    const PuzzleState initialState({A, B, C}, {Segment(A, B), Segment(B, C), Segment(C, A)}, {}, {});
    
    PuzzleState tmp = initialState;
    tmp.drawCircle(A, C);
    Point E(tmp.points[tmp.points.size()-1]);
    tmp.drawCircle(C, E);
    tmp.drawCircle(E, C);
    Point H(tmp.points[tmp.points.size()-1]);
    std::cout << "tmp has " << tmp.points.size() << "points" << std::endl;
    for (auto point: tmp.points)
        std::cout << CGAL::to_double(point.x()) << " " << CGAL::to_double(point.y()) << std::endl;

    std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;

    Line bisector1(A, H);

    const PuzzleState goalState({}, {}, {}, {});
    const int optimalDepth = 4;
    return Puzzle(initialState, goalState, optimalDepth);
}

Puzzle beta8_tangent_to_line_at_point() {
    Point A(0, 0), B(1, 0);
    Point C(0.6, 1.33), D(1.26, 0.58);
    const PuzzleState initialState({A, B}, {}, {}, {PuzzleState::createCircle(A, B)});
    Point E(1, 1);
    const PuzzleState goalState({}, {}, {Line(B, E)}, {});
    const int optimalDepth = 3;
    return Puzzle(initialState, goalState, optimalDepth);
}