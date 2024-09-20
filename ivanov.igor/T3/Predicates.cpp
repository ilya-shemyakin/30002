#include <algorithm>

#include "Predicates.h"

namespace ivanov
{
    bool hasEvenVertexesCount(const Polygon& polygon)
    {
        return polygon.points.size() % 2 == 0;
    }

    bool hasOddVertexesCount(const Polygon& polygon)
    {
        return !hasEvenVertexesCount(polygon);
    }

    bool checkVertexesCount(const Polygon& polygon, std::size_t num)
    {
        return polygon.points.size() == num;
    }

    bool isLessArea(const Polygon& lhs, const Polygon& rhs)
    {
        return lhs.computeArea() < rhs.computeArea();
    }

    bool isLessVertexesCount(const Polygon& lhs, const Polygon& rhs)
    {
        return lhs.points.size() < rhs.points.size();
    }


}
