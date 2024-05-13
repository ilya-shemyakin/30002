#ifndef VEC_H
#define VEC_H

#include "Point.h"
#include <cmath>

struct Vec {
    double x, y;
public:
    Vec(double x = 0, double y = 0);
    Vec(const Point& a, const Point& b);
    double operator/(const Vec& other);
};

#endif
