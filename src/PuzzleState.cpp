#include "PuzzleState.h"
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#include <CGAL/intersections.h>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;


PuzzleState::PuzzleState(const std::vector<Point>& pointsVec, const std::vector<Line>& linesVec, const std::vector<Circle>& circlesVec) {
    // Initialize the state from the provided vectors
    points = pointsVec;
    lines = linesVec;
    circles = circlesVec;
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

bool findCircleLineIntersections(const Circle& circle, const Line& line, Point& intersection1, Point& intersection2) {
    // std::vector<Point> intersections;
    // CGAL::intersection(circle, line, std::back_inserter(intersections));
    
    // if (intersections.size() == 2) {
    //     intersection1 = intersections[0];
    //     intersection2 = intersections[1];
    //     return true;
    // } else {
    //     return false;
    // }
    return false;
}


void PuzzleState::drawLine(const Point& start, const Point& end) {
    // Create a new line based on the start and end points
    Line newLine(start, end);


    // Check for intersections with existing lines and circles
    for (const Line& existingLine : lines) {
        Point intersection;
        std::cout << "Comparing to " << existingLine << std::endl;
        if (findLineIntersection(newLine, existingLine, intersection)) {
            std::cout << "Found intersection " << intersection << std::endl;
            points.push_back(intersection);
        }
    }

    for (const Circle& existingCircle : circles) {
        Point intersection1, intersection2;
        if (findCircleLineIntersections(existingCircle, newLine, intersection1, intersection2)) {
            points.push_back(intersection1);
            points.push_back(intersection2);
        }
    }

    lines.push_back(newLine);
}