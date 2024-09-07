#ifndef PREDICATES_H
#define PREDICATES_H

#include <functional>

#include "Polygon.h"

namespace maltsev
{
  bool hasEvenVertexesCount(const Polygon& polygon);
  bool hasOddVertexesCount(const Polygon& polygon);
  bool checkVertexesCount(const Polygon& polygon, std::size_t num);
  bool isLessArea(const Polygon& lhs, const Polygon& rhs);
  bool isLessVertexesCount(const Polygon& lhs, const Polygon& rhs);
  bool hasIntersection(const Polygon& lhs, const Polygon& rhs);
  bool isEcho(const Polygon& lhs, const Polygon& rhs, const Polygon& target);
}

#endif
