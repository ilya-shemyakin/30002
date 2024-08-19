#include "Point.h"

namespace shapes
{
    bool Point::operator==(const Point& point) const
    {
        return (x == point.x) && (y == point.y);
    }
}
