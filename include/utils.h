#pragma once
#include <unordered_set>
#include <vector>
#include <functional>
#include <algorithm>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>

using Kernel = CGAL::Exact_circular_kernel_2;
using Segment = Kernel::Segment_2;
using Circular_arc_point = Kernel::Circular_arc_point_2;


const extern float DISTANCE_THRESHOLD;
const extern float DISTANCE_INVERSE_THRESHOLD;

template <class T>
inline void hash_combine(std::size_t & seed, const T & v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}


template <typename T>
std::size_t hashSet(const std::unordered_set<T>& set) {
  std::vector<size_t> hashes;
  for (const auto& element: set)
    hashes.push_back(std::hash<T>()(element));
  // We hash the sorted vector.
  // TODO: should we use set instead of unordered_set? It's already sorted by hashes?
  // TODO: consider summing/xoring the hashes rather than sorting, for efficiency.
  std::sort(hashes.begin(), hashes.end());
  std::size_t hash_value = 0;
  for (const size_t& element_hash : hashes)
      hash_combine(hash_value, element_hash);
  return hash_value;
}

template <typename T>
std::vector<T> unorderedSetDifference(const std::unordered_set<T>& plus, const std::unordered_set<T>& minus){
  std::vector<T> difference;
  for (const auto& elem : plus){
    if (!minus.count(elem))
      difference.push_back(elem);
  }
  return difference;
}


/** Point */

class Point : public Kernel::Point_2 {
public:
    Point(double x, double y) : Kernel::Point_2(x, y) {}
    Point(Kernel::Point_2 p) : Kernel::Point_2(p) {}
    Point() : Kernel::Point_2() {}
    std::size_t hash() const;
    bool operator==(const Point& other) const;
    bool isValid() const;
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
    std::size_t hash() const;
    bool operator==(const Circle& other) const;
    Point randomPoint() const {
        const Point reference(0.1, -0.5);
        Kernel::Vector_2 delta = reference - center();
        const Point point = center() + std::sqrt(CGAL::to_double(squared_radius())) * delta / std::sqrt(CGAL::to_double(delta.squared_length()));
        return point;
    }
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
    std::size_t hash() const;
    bool operator==(const Line& other) const;
    Point randomPoint() const {
        const Point reference(0.567, 0.890);
        return Point(projection(reference));
    }
};
std::ostream& operator << ( std::ostream& outs, const Line & l);

namespace std {
    template <>
    struct hash<Line> {
        std::size_t operator()(const Line& l) const {
            return l.hash();
        }
    };
};



// TODO: move this to class functions?
namespace Utils
{
  bool isOn(const Point& point, const Line& line, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Segment& segment, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Circle& circle, const float maxDistance = DISTANCE_THRESHOLD);
}
