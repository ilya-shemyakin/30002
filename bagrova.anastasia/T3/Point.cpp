#include "Point.h"
#include <iostream>

Point::Point(int x, int y) :
        x(x),
        y(y) {}

bool PointsComparator::operator()(const Point& p1, const Point& p2) const {
    return p1.x < p2.x || p1.x == p2.x && p1.y < p2.y;
}

std::ostream& operator<<(std::ostream& out, const Point& point) {
    return out << " (" << point.x << ";" << point.y << ")";
}
