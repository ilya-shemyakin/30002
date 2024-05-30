#include <algorithm>

#include "Predicates.h"

namespace yurev
{
    bool hasEvenVertexesCount(const Polygon &polygon)
    {
        return polygon.points.size() % 2 == 0;
    }

    bool hasOddVertexesCount(const Polygon &polygon)
    {
        return !hasEvenVertexesCount(polygon);
    }

    bool checkVertexesCount(const Polygon &polygon, std::size_t num)
    {
        return polygon.points.size() == num;
    }

    bool isLessArea(const Polygon &lhs, const Polygon &rhs)
    {
        return lhs.computeArea() < rhs.computeArea();
    }

    bool isLessVertexesCount(const Polygon &lhs, const Polygon &rhs)
    {
        return lhs.points.size() < rhs.points.size();
    }

    bool hasIntersection(const Polygon &lhs, const Polygon &rhs)
    {
        const auto minMaxLhs = std::minmax_element(lhs.points.cbegin(), lhs.points.cend());
        const auto minMaxRhs = std::minmax_element(rhs.points.cbegin(), rhs.points.cend());
        const auto &maxLhs = *(minMaxLhs.second);
        const auto &minLhs = *(minMaxLhs.first);
        const auto &maxRhs = *(minMaxRhs.second);
        const auto &minRhs = *(minMaxRhs.first);

        return !((maxRhs < minLhs) || (maxLhs < minRhs));
    }

    bool isRect(const Polygon &p)
    {
        return p.points.size() == 4;
    }
}
