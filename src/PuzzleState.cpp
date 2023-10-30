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
    const std::vector<Segment>& segmentsVec,
    const std::vector<Line>& linesVec,
    const std::vector<Circle>& circlesVec
) : points(pointsVec), segments(segmentsVec), lines(linesVec), circles(circlesVec) {
}

PuzzleState& PuzzleState::operator=(const PuzzleState& other) {
    if (this == &other) {
        return *this;
    }
    points = other.points;
    segments = other.segments;
    lines = other.lines;
    circles = other.circles;
    return *this;
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

bool PuzzleState::findLineIntersection(const Line& line1, const Segment& line2, Point& intersection) {
    const bool hasIntersection = findLineIntersection(line1, Line(line2.start(), line2.end()), intersection);
    return hasIntersection && line2.has_on(intersection);
}

bool PuzzleState::findCircleIntersections(const Circle& circle, const Segment& line, std::vector<Point>& intersections) {
    std::vector<Point> candidates;
    const bool hasIntersection = findCircleIntersections(circle, Line(line.start(), line.end()), candidates);
    for (const auto& candidate: candidates) {
        if (line.has_on(candidate))
        intersections.push_back(candidate);
    }
    return hasIntersection && !intersections.empty();
}

bool PuzzleState::findCircleIntersections(const Circle& circle, const Line& line, std::vector<Point>& intersections) {
    std::vector<CGAL::Object> allIntersections;
    CGAL::intersection(circle, line, std::back_inserter(allIntersections));

    for (const CGAL::Object& obj : allIntersections) {
        if (const std::pair<Circular_arc_point, unsigned>* pair = CGAL::object_cast<std::pair<Circular_arc_point, unsigned>>(&obj)) {
            intersections.push_back(Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y())));
        }
    }
    return !intersections.empty();
}

bool PuzzleState::findCircleIntersections(const Circle& circle1, const Circle& circle2, std::vector<Point>& intersections) {
    std::vector<CGAL::Object> allIntersections;
    CGAL::intersection(circle1, circle2, std::back_inserter(allIntersections));

    for (const CGAL::Object& obj : allIntersections) {
        if (const std::pair<Circular_arc_point, unsigned>* pair = CGAL::object_cast<std::pair<Circular_arc_point, unsigned>>(&obj)) {
            intersections.push_back(Point(CGAL::to_double(pair->first.x()), CGAL::to_double(pair->first.y())));
        }
    }
    return !intersections.empty();
}

void PuzzleState::maybeAddPoint(const Point& point) {
    // TODO: use std::unordered_set
    if (std::find(points.begin(), points.end(), point) == points.end()) {
        points.push_back(point);
    }
}

void PuzzleState::maybeAddLine(const Line& line) {
    // TODO: use std::unordered_set
    if (std::find(lines.begin(), lines.end(), line) == lines.end() &&
        std::find(lines.begin(), lines.end(), line.opposite()) == lines.end()) {
        lines.push_back(line);
    }
}

void PuzzleState::maybeAddCircle(const Circle& circle) {
    // TODO: use std::unordered_set
    if (std::find(circles.begin(), circles.end(), circle) == circles.end() &&
        std::find(circles.begin(), circles.end(), circle.opposite()) == circles.end()) {
        circles.push_back(circle);
    }
}

void PuzzleState::drawLine(const Point& start, const Point& end) {
    Line newLine(start, end);

    for (const Segment& existingSegment : segments) {
        Point intersection;
        if (findLineIntersection(newLine, existingSegment, intersection)) {
            maybeAddPoint(intersection);
        }
    }
    
    for (const Line& existingLine : lines) {
        Point intersection;
        if (findLineIntersection(newLine, existingLine, intersection)) {
            maybeAddPoint(intersection);
        }
    }
    
    for (const Circle& existingCircle : circles) {
        std::vector<Point> intersections;
        if (findCircleIntersections(existingCircle, newLine, intersections)) {
            for (const auto& intersection: intersections) {
                maybeAddPoint(intersection);
            }
        }
    }

    maybeAddLine(newLine);
}


void PuzzleState::drawCircle(const Point& center, const Point& pointOnCircle) {
    const auto newCircle = createCircle(center, pointOnCircle);

    for (const Segment& existingSegment : segments) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingSegment, intersections)) {
            for (const auto& intersection: intersections) {
                maybeAddPoint(intersection);
            }
        }
    }

    for (const Line& existingLine : lines) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingLine, intersections)) {
            for (const auto& intersection: intersections) {
                maybeAddPoint(intersection);
            }
        }
    }

    for (const Circle& existingCircle : circles) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingCircle, intersections)) {
            for (const auto& intersection: intersections) {
                maybeAddPoint(intersection);
            }
        }
    }

    maybeAddCircle(newCircle);
}