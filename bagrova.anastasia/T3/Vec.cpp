#include "Vec.h"
#include "Point.h"

Vec::Vec(double x, double y) :
    x(x),
    y(y) {}

Vec::Vec(const Point& a, const Point& b) :
        Vec(b.x - a.x, b.y - a.y) {}

double Vec::operator/(const Vec& other) {
    if (abs(other.x) > 1E-6) {
        return x / other.x;
    }
    return y / other.y;
}
