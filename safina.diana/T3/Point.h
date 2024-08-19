#ifndef POINT_H
#define POINT_H

namespace shapes
{
    struct Point
    {
        int x, y;
        bool operator==(const Point& point) const;
    };
}

#endif
