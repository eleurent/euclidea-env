#include "PuzzleState.h"
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>

typedef CGAL::CK2_Intersection_traits<Kernel, Kernel::Circle_2, Kernel::Circle_2>::type Intersection_result;


PuzzleState::PuzzleState(
    const std::unordered_set<Point>& pointsSet,
    const std::vector<Segment>& segmentsVec,
    const std::unordered_set<Line>& linesSet,
    const std::unordered_set<Circle>& circlesSet
) : points(pointsSet), segments(segmentsVec), lines(linesSet), circles(circlesSet) {
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

std::size_t PuzzleState::hash() const {
    // Note we don't hash segments as they cannot be modified by the user
    size_t pointsHash = hashSet<Point>(points);
    size_t linesHash = hashSet<Line>(lines);
    size_t circlesHash = hashSet<Circle>(circles);
    size_t hashValue = 0;
    hash_combine(hashValue, pointsHash);
    hash_combine(hashValue, linesHash);
    hash_combine(hashValue, circlesHash);
    return hashValue;
}

bool PuzzleState::operator==(const PuzzleState& other) const {
    // We don't compare segments
    return hash() == other.hash();
}


bool PuzzleState::findLineIntersection(const Line& line1, const Line& line2, Point& intersection) {
    std::vector<CGAL::Object> intersections;
    CGAL::intersection(line1, line2, std::back_inserter(intersections));

    if (!intersections.empty()) {
        if (const Kernel::Point_2* p = CGAL::object_cast<Kernel::Point_2>(&intersections.front())) {
            intersection = Point(*p);
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
        if (Utils::isOn(candidate, line))
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


void PuzzleState::drawLine(const Point& start, const Point& end) {
    Line newLine(start, end);

    points.insert(start);
    points.insert(end);

    for (const Segment& existingSegment : segments) {
        Point intersection;
        if (findLineIntersection(newLine, existingSegment, intersection)) {
            points.insert(intersection);
        }
    }
    
    for (const Line& existingLine : lines) {
        Point intersection;

        if (findLineIntersection(newLine, existingLine, intersection)) {
            points.insert(intersection);
        }
    }
    
    for (const Circle& existingCircle : circles) {
        std::vector<Point> intersections;
        if (findCircleIntersections(existingCircle, newLine, intersections)) {
            for (const auto& intersection: intersections) {
                points.insert(intersection);
            }
        }
    }

    lines.insert(newLine);
}


void PuzzleState::drawCircle(const Point& center, const Point& pointOnCircle) {
    const auto newCircle = Circle::fromRadius(center, pointOnCircle);
    
    points.insert(center);
    points.insert(pointOnCircle);

    for (const Segment& existingSegment : segments) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingSegment, intersections)) {
            for (const auto& intersection: intersections) {
                if (intersection.isValid())
                    points.insert(intersection);
            }
        }
    }

    for (const Line& existingLine : lines) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingLine, intersections)) {
            for (const auto& intersection: intersections) {
                if (intersection.isValid())
                    points.insert(intersection);
            }
        }
    }

    for (const Circle& existingCircle : circles) {
        std::vector<Point> intersections;
        if (findCircleIntersections(newCircle, existingCircle, intersections)) {
            for (const auto& intersection: intersections) {
                if (intersection.isValid())
                    points.insert(intersection);
            }
        }
    }

    circles.insert(newCircle);
}