#pragma once
#include <vector>
#include <unordered_set>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include "utils.h"


class PuzzleState {
public:
    PuzzleState(const std::unordered_set<Point>& pointsSet, const std::vector<Segment>& segmentsVec, const std::unordered_set<Line>& linesSet, const std::unordered_set<Circle>& circlesSet);
    PuzzleState& operator=(const PuzzleState& rhs);

    void drawLine(const Point& start, const Point& end);
    void drawCircle(const Point& center, const Point& pointOnCircle);

    std::unordered_set<Point> points;
    std::vector<Segment> segments;
    std::unordered_set<Line> lines;
    std::unordered_set<Circle> circles;    
private:

    bool findLineIntersection(const Line& line1, const Line& line2, Point& intersection);
    bool findLineIntersection(const Line& line1, const Segment& line2, Point& intersection);
    bool findCircleIntersections(const Circle& circle, const Line& line, std::vector<Point>& intersections);
    bool findCircleIntersections(const Circle& circle, const Segment& line, std::vector<Point>& intersections);
    bool findCircleIntersections(const Circle& circle1, const Circle& circle2, std::vector<Point>& intersections);
};