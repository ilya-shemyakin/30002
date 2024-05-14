#ifndef FUNCTORS_H
#define FUNCTORS_H

#include <functional>

#include "Point.h"
#include "Polygon.h"

namespace maltsev
{
  struct AccumulatePolygonArea
  {
    Point p1;
    double operator()(double acc, const Point& p2, const Point& p3);
  };
}

#endif
