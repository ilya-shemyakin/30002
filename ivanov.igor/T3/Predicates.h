// Predicates.h
#ifndef PREDICATES_H_
#define PREDICATES_H_

#include <functional>

#include "Polygon.h"

namespace ivanov
{
    bool hasEvenVertexesCount(const Polygon& polygon);
    bool hasOddVertexesCount(const Polygon& polygon);
    bool checkVertexesCount(const Polygon& polygon, std::size_t num);
    bool isLessArea(const Polygon& lhs, const Polygon& rhs);
    bool isLessVertexesCount(const Polygon& lhs, const Polygon& rhs);
}

#endif // PREDICATES_H_
