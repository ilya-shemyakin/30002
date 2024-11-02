#ifndef PREDICATES_H
#define PREDICATES_H

#include <functional>

#include "Polygon.h"

namespace khizhnichenko {
  bool hasEvenVertexesCount(const Polygon& polygon);
  bool hasOddVertexesCount(const Polygon& polygon);
  bool checkVertexesCount(const Polygon& polygon, std::size_t num);
  bool isLessArea(const Polygon& lhs, const Polygon& rhs);
  bool isLessVertexesCount(const Polygon& lhs, const Polygon& rhs);
  bool isRectangle(const Polygon& polygon);
}

#endif
