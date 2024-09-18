// Functors.h
#ifndef FUNCTORS_H_
#define FUNCTORS_H_

#include "Point.h"
#include "Polygon.h"

namespace ivanov
{
    struct AccumulatePolygonArea
    {
        Point p1;
        double operator()(double acc, const Point& p2, const Point& p3);
    };
}

#endif // FUNCTORS_H_
