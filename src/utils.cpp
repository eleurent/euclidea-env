#include "utils.h"

const float DISTANCE_THRESHOLD = 1e-5f;
const float DISTANCE_INVERSE_THRESHOLD = 10000;

bool Point::operator==(const Point& other) const {
    return hash() == other.hash();
}

std::size_t Point::hash() const {
    int rounded_x = static_cast<int>(CGAL::to_double(x()) * DISTANCE_INVERSE_THRESHOLD);
    int rounded_y = static_cast<int>(CGAL::to_double(y()) * DISTANCE_INVERSE_THRESHOLD);
    std::size_t hash_value = 0;
    hash_combine(hash_value, rounded_x);
    hash_combine(hash_value, rounded_y);

    return hash_value;
}

std::ostream& operator << ( std::ostream& outs, const Point & p )
{
  return outs << "(" <<  CGAL::to_double(p.x()) << "," << CGAL::to_double(p.y()) << ")";
}


Circle Circle::fromRadius(const Point& center, const Point& pointOnCircle) {
  return Circle(center - (pointOnCircle - center), pointOnCircle);
};

bool Circle::operator==(const Circle& other) const {
    return hash() == other.hash();
}

std::size_t Circle::hash() const {
    std::size_t hash_value = 0;
    hash_combine(hash_value, Point(center()).hash());
    hash_combine(hash_value, static_cast<int>(CGAL::to_double(squared_radius()) * DISTANCE_INVERSE_THRESHOLD));

    return hash_value;
}

std::ostream& operator << ( std::ostream& outs, const Circle & c )
{
  return outs << "[" << Point(c.center()) << ", " << c.squared_radius() << "]";
}


bool Line::operator==(const Line& other) const {
    return hash() == other.hash();
}

std::size_t Line::hash() const {
    std::size_t hash_value = 0;
    double an = CGAL::to_double(a());
    double bn = CGAL::to_double(b());
    double cn = CGAL::to_double(c());
    // Canonized direction, to hash this and this.opposite()
    if ((an < -DISTANCE_THRESHOLD) || ((std::abs(an) < DISTANCE_THRESHOLD) && (bn < -DISTANCE_THRESHOLD))) {
      an = -an;
      bn = -bn;
      cn = -cn;
    }
    hash_combine(hash_value, static_cast<int>(an * DISTANCE_INVERSE_THRESHOLD));
    hash_combine(hash_value, static_cast<int>(bn * DISTANCE_INVERSE_THRESHOLD));
    hash_combine(hash_value, static_cast<int>(cn * DISTANCE_INVERSE_THRESHOLD));
    return hash_value;
}


namespace Utils {
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