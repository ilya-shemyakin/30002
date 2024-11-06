#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Point.h"

struct Polygon {
    std::vector< Point > points;

    bool operator ==(const Polygon& other) const;
    bool operator !=(const Polygon& other) const;
    bool operator <(const Polygon& other) const;

    double area(void) const;
    bool rightTriangle(const Point& p1, const Point& p2, const Point& p3) const;
};

bool rightAngle(const Polygon& poly);

std::istream& operator>>(std::istream& in, Polygon& polygon);
std::ostream& operator<< (std::ostream& out, const Polygon& poly);

#endif
