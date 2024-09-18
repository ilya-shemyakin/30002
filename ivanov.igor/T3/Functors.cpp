#include "Functors.h"

namespace ivanov
{
    double AccumulatePolygonArea::operator()(double acc, const Point& p2, const Point& p3)
    {
        acc += 0.5 * std::abs((p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
        p1 = p2;
        return acc;
    }
}
