#include "Polygon.h"

namespace shapes
{
    bool Polygon::operator==(const Polygon& polygon) const
    {
        return points == polygon.points;
    }
}
