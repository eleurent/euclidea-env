#pragma once
#include <vector>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <functional>

using Kernel = CGAL::Exact_circular_kernel_2;
// using Point = Kernel::Point_2;
using Segment = Kernel::Segment_2;
// using Line = Kernel::Line_2;
// using Circle = Kernel::Circle_2;
using Circular_arc_point = Kernel::Circular_arc_point_2;


const extern float DISTANCE_THRESHOLD;
const extern float DISTANCE_INVERSE_THRESHOLD;


template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


/** Point */

class Point : public Kernel::Point_2 {
public:
    Point(double x, double y) : Kernel::Point_2(x, y) {}
    Point(Kernel::Point_2 p) : Kernel::Point_2(p) {}
    Point() : Kernel::Point_2() {}
    bool operator==(const Point& other) const;
    std::size_t hash() const;
};

namespace std {
    template <>
    struct hash<Point> {
        std::size_t operator()(const Point& p) const {
            return p.hash();
        }
    };
};
std::ostream& operator << ( std::ostream& outs, const Point & p );


/** Circle */

class Circle : public Kernel::Circle_2 {
public:
    Circle(Point x, Point y) : Kernel::Circle_2(x, y) {}
    Circle(Kernel::Circle_2 p) : Kernel::Circle_2(p) {}
    Circle() : Kernel::Circle_2() {}
    static Circle fromRadius(const Point& center, const Point& pointOnCircle);
    bool operator==(const Circle& other) const;
    std::size_t hash() const;
};

namespace std {
    template <>
    struct hash<Circle> {
        std::size_t operator()(const Circle& c) const {
            return c.hash();
        }
    };
};
std::ostream& operator << ( std::ostream& outs, const Circle & c );


/** Line */

class Line : public Kernel::Line_2 {
public:
    Line(Point x, Point y) : Kernel::Line_2(x, y) {}
    Line(Kernel::Line_2 l) : Kernel::Line_2(l) {}
    Line() : Kernel::Line_2() {}
    bool operator==(const Line& other) const;
    std::size_t hash() const;
};

namespace std {
    template <>
    struct hash<Line> {
        std::size_t operator()(const Line& l) const {
            return l.hash();
        }
    };
};


namespace Utils
{
  bool isOn(const Point& point, const Line& line, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Segment& segment, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Circle& circle, const float maxDistance = DISTANCE_THRESHOLD);
}
