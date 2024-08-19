#ifndef POLYGON_H
#define POLYGON_H

#include <iostream>
#include <vector>

#include "Point.h"

namespace shapes
{
    struct Polygon
    {
        std::vector< Point > points;
        bool operator==(const Polygon& polygon) const;
    };
}

#endif
