#include "utils.h"


namespace Utils {
  const float DISTANCE_THRESHOLD = 1e-5f;

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
  bool isOn(const Point& point, const Segment& line, const float maxDistance) {
    // Replaces Line::has_on
    return CGAL::squared_distance(point, line) < maxDistance;
  }
}

