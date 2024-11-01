#include "InputFormatters.h"
#include "Point.h"
//#include "Delimiter.h"


bool Point::operator==(const Point& other) const {
    return (x == other.x) && (y == other.y);
}

bool Point::operator<(const Point& other) const {
    return x < other.x && y < other.y;
}

std::istream& operator>>(std::istream& in, Point& pnt) {
    std::istream::sentry sentry(in);

    if (!sentry)
        return in;

    in >> DelimiterI{ '(' } >> pnt.x >> DelimiterI{ ';' } >> pnt.y >> DelimiterI{ ')' };

    return in;
}

std::ostream& operator<<(std::ostream& out, const Point& pnt) {
    std::ostream::sentry sentry(out);

    if (!sentry)
        return out;

    out << '(' << pnt.x << ';' << pnt.y << ')';
    return out;
}

double Point::length(const Point& other) const {
    return sqrt(pow(other.x - x, 2) + pow(other.y - y, 2));
}
