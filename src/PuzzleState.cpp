#include "PuzzleState.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;



PuzzleState::PuzzleState(
    const std::vector<Point>& pointsVec,
    const std::vector<Line>& linesVec,
    const std::vector<Circle>& circlesVec
) : points(pointsVec), lines(linesVec), circles(circlesVec) {
}

bool findLineIntersection(const Line& line1, const Line& line2, Point& intersection) {
    CGAL::Object result = CGAL::intersection(line1, line2);
    
    if (const Point* p = CGAL::object_cast<Point>(&result)) {
        intersection = *p;
        return true;
    } else {
        return false;
    }
}


void PuzzleState::maybeAddPoint(const Point& point) {
    // TODO: use std::unordered_set
    bool pointExists = false;
    for (const Point& existingPoint : points) {
        if (existingPoint == point) {
            pointExists = true;
            break;
        }
    }
    if (!pointExists) {
        points.push_back(point);
    }
}

void PuzzleState::maybeAddLine(const Line& line) {
    // TODO: use std::unordered_set
    bool exists = false;
    for (const Line& existingLine : lines) {
        if (existingLine == line) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        lines.push_back(line);
    }
}

void PuzzleState::drawLine(const Point& start, const Point& end) {
    Line newLine(start, end);

    for (const Line& existingLine : lines) {
        Point intersection;
        std::cout << "Comparing to " << existingLine << std::endl;
        if (findLineIntersection(newLine, existingLine, intersection)) {
            std::cout << "Found intersection " << intersection << std::endl;
            maybeAddPoint(intersection);
        }
    }

    maybeAddLine(newLine);
}