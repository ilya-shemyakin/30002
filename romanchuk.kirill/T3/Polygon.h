#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Point.h"

struct Polygon
{
  std::vector< Point > points;
};

std::istream& operator>>(std::istream& in, Polygon& polygon);
std::ostream& operator<<(std::ostream& out, const Polygon& polygon);

#endif // !POLYGON_H
