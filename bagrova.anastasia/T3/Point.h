#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
    int x, y;
    Point(int x = 0, int y = 0);
};

std::ostream& operator<<(std::ostream& out, const Point& point);

struct PointsComparator {
    bool operator()(const Point& p1, const Point& p2) const;
};
#endif
