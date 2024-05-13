#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <vector>

struct Polygon {
    std::vector< Point > points;
    double area() const;
    bool hasMutualPoint(const Polygon& other) const;
    bool containsPoint(const Point& point) const;
    bool intersect(const Polygon& other) const;
};

std::ostream& operator<<(std::ostream& out, const Polygon& poly);
#endif
