#include "PuzzleState.h"
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>

using Kernel = CGAL::Exact_circular_kernel_2;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;
using Circular_arc_point = Kernel::Circular_arc_point_2;
typedef CGAL::CK2_Intersection_traits<Kernel, Circle, Circle>::type Intersection_result;



PuzzleState::PuzzleState(
    const std::vector<Point>& pointsVec,
    const std::vector<Line>& linesVec,
    const std::vector<Circle>& circlesVec
) : points(pointsVec), lines(linesVec), circles(circlesVec) {
}

bool PuzzleState::findLineIntersection(const Line& line1, const Line& line2, Point& intersection) {
    std::vector<CGAL::Object> intersections;
    CGAL::intersection(line1, line2, std::back_inserter(intersections));

    if (!intersections.empty()) {
        if (const Point* p = CGAL::object_cast<Point>(&intersections.front())) {
            intersection = *p;
            return true;
        }
    }
    return false;
}

bool PuzzleState::findCircleLineIntersections(const Circle& circle, const Line& line, Point& intersection1, Point& intersection2) {
    std::vector<CGAL::Object> intersections;
    CGAL::intersection(circle, line, std::back_inserter(intersections));

    if (!intersections.empty()) {
        if (const std::pair<Circular_arc_point, unsigned>* pair = CGAL::object_cast<std::pair<Circular_arc_point, unsigned>>(&intersections.front())) {
            intersection1 = Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y()));
            intersection2 = Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y()));
            // Handle the multiplicity if needed
            // pair->second contains the multiplicity
            return true;
        } else  {
            return false;
        }
    }
    return false;
}

bool PuzzleState::findCircleIntersections(const Circle& circle1, const Circle& circle2, Point& intersection1, Point& intersection2) {
    std::vector<CGAL::Object> intersections;
    CGAL::intersection(circle1, circle2, std::back_inserter(intersections));

    if (!intersections.empty()) {
        if (const std::pair<Circular_arc_point, unsigned>* pair = CGAL::object_cast<std::pair<Circular_arc_point, unsigned>>(&intersections.front())) {
            intersection1 = Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y()));
            intersection2 = Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y()));
            // Handle the multiplicity if needed
            // pair->second contains the multiplicity
            return true;
        } else {
            return false;
        }
    }
    return false;
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

void PuzzleState::maybeAddCircle(const Circle& circle) {
    // TODO: use std::unordered_set
    bool exists = false;
    for (const Circle& existingCircle : circles) {
        if (existingCircle == circle) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        circles.push_back(circle);
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

    
    for (const Circle& existingCircle : circles) {
        Point intersection1, intersection2;
        if (findCircleLineIntersections(existingCircle, newLine, intersection1, intersection2)) {
            maybeAddPoint(intersection1);
            maybeAddPoint(intersection2);
        }
    }

    maybeAddLine(newLine);
}


void PuzzleState::drawCircle(const Point& center, const Point& pointOnCircle) {
    Circle newCircle(center, pointOnCircle);

    for (const Line& existingLine : lines) {
        Point intersection1, intersection2;
        if (findCircleLineIntersections(newCircle, existingLine, intersection1, intersection2)) {
            maybeAddPoint(intersection1);
            maybeAddPoint(intersection2);
        }
    }

    for (const Circle& existingCircle : circles) {
        Point intersection1, intersection2;
        if (findCircleIntersections(existingCircle, newCircle, intersection1, intersection2)) {
            maybeAddPoint(intersection1);
            maybeAddPoint(intersection2);
        }
    }

    maybeAddCircle(newCircle);
}