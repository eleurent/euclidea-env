#include "utils.h"

const float DISTANCE_THRESHOLD = 1e-5f;

bool Point::operator==(const Point& other) const {
    return hash() == other.hash();
}

std::size_t Point::hash() const {
    int rounded_x = static_cast<int>(CGAL::to_double(x()) * 10000);
    int rounded_y = static_cast<int>(CGAL::to_double(y()) * 10000);
    std::size_t hash_value = 0;
    hash_combine(hash_value, rounded_x);
    hash_combine(hash_value, rounded_y);

    return hash_value;
}

std::ostream& operator << ( std::ostream& outs, const Point & p )
{
  return outs << "(" <<  CGAL::to_double(p.x()) << "," << CGAL::to_double(p.y()) << ")";
}

namespace Utils {

  std::string toString(const Point point) {
    std::ostringstream stringStream;
    stringStream << "(" << CGAL::to_double(point.x()) << ", " << CGAL::to_double(point.y()) << ")";
    return stringStream.str();
  }

  bool find(const Point& point, const std::vector<Point>& points, const float maxDistance) {
    // Replaces std::find
    for (const auto other: points) {
        if (CGAL::squared_distance(point, other) < maxDistance) {
            return true;
        }
    }
    return false;
  }

  bool isOn(const Point& point, const Line& line, const float maxDistance) {
    // Replaces Line::has_on
    return CGAL::squared_distance(point, line) < maxDistance;
  }
  bool isOn(const Point& point, const Segment& segment, const float maxDistance) {
    // Replaces Segment::has_on
    return CGAL::squared_distance(point, segment) < maxDistance;
  }
  bool isOn(const Point& point, const Circle& circle, const float maxDistance) {
    // Replaces Circle::has_on
    Point center(circle.center());
    return maxDistance - circle.squared_radius() < CGAL::squared_distance(point, center) < maxDistance + circle.squared_radius();
  }
}