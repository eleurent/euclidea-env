#pragma once
#include <vector>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>

using Kernel = CGAL::Exact_circular_kernel_2;
using Point = Kernel::Point_2;
using Segment = Kernel::Segment_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;


namespace Utils
{
  const extern float DISTANCE_THRESHOLD;

  std::string toString(const Point point);

  bool find(const Point& point, const std::vector<Point>& points, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Line& line, const float maxDistance = DISTANCE_THRESHOLD);
  bool isOn(const Point& point, const Segment& line, const float maxDistance = DISTANCE_THRESHOLD);
}