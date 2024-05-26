#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

#include "Point.h"

namespace maltsev
{
  struct Polygon
  {
    std::vector< Point > points;

    double computeArea() const;
    bool operator==(const Polygon& other) const;
  };

  std::istream& operator>>(std::istream& in, Polygon& dest);
  std::ostream& operator<<(std::ostream& out, const Polygon& polygon);
}

#endif
