// Polygon.h
#ifndef POLYGON_H_
#define POLYGON_H_

#include <iostream>
#include <vector>

#include "Point.h"

namespace yurev
{
    struct Polygon
    {
        std::vector<Point> points;

        double computeArea() const;
        bool operator==(const Polygon &other) const;
    };

    std::istream &operator>>(std::istream &in, Polygon &dest);
    std::ostream &operator<<(std::ostream &out, const Polygon &polygon);
}

#endif // POLYGON_H_
