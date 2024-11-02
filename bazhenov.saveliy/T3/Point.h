#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point {
    int x, y;

    bool operator==(const Point& other) const;
    bool operator<(const Point& other) const;

    double length(const Point& other) const;
};

std::istream& operator>>(std::istream& in, Point& dest);
std::ostream& operator<<(std::ostream& out, const Point& point);

#endif
