#pragma once
#include <vector>
#include <CGAL/Exact_circular_kernel_2.h>
#include <CGAL/Circular_kernel_intersections.h>

using Kernel = CGAL::Exact_circular_kernel_2;
using Point = Kernel::Point_2;
using Segment = Kernel::Segment_2;
using Line = Kernel::Line_2;
using Circle = Kernel::Circle_2;

std::string toString(const Point point) {
  std::ostringstream stringStream;
  stringStream << "(" << CGAL::to_double(point.x()) << ", " << CGAL::to_double(point.y()) << ")";
  return stringStream.str();
}