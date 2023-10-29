#pragma once

#include <vector>

struct Point {
    double x, y;
};

struct Line {
    Point start, end;
};

struct Circle {
    Point center;
    Point radius;
};

struct PuzzleState {
    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Circle> circles;
};