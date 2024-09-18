// Point.h
#ifndef POINT_H_
#define POINT_H_

#include <iostream>

namespace ivanov
{
    struct Point
    {
        int x, y;
        bool operator==(const Point& other) const;
        bool operator<(const Point& other) const;
    };
    std::istream& operator>>(std::istream& in, Point& dest);
    std::ostream& operator<<(std::ostream& out, const Point& point);
}

#endif // POINT_H_
#pragma once
