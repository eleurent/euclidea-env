#pragma once

#include <vector>
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>

using Kernel = CGAL::Exact_predicates_exact_constructions_kernel;
using Point = Kernel::Point_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;


class PuzzleState {
public:
    PuzzleState(const std::vector<Point>& pointsVec, const std::vector<Line>& linesVec, const std::vector<Circle>& circlesVec);

    void maybeAddPoint(const Point& point);
    void maybeAddLine(const Line& line);
    
    void drawLine(const Point& start, const Point& end);

    std::vector<Point> points;
    std::vector<Line> lines;
    std::vector<Circle> circles;
private:

};