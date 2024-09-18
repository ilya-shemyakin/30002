#include "IOHelpers.h"
#include "Point.h"

namespace ivanov
{
    bool Point::operator==(const Point& other) const
    {
        return (x == other.x) && (y == other.y);
    }

    bool Point::operator<(const Point& other) const
    {
        return x < other.x && y < other.y;
    }

    std::istream& operator>>(std::istream& in, Point& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        using chr = ExpectedCharIO;
        Point temp{ 0, 0 };
        in >> chr{ '(' } >> temp.x >> chr{ ';' } >> temp.y >> chr{ ')' };

        if (in)
        {
            dest = temp;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Point& pnt)
    {
        std::ostream::sentry guard(out);
        if (!guard)
        {
            return out;
        }
        out << "(" << pnt.x << "; " << pnt.y << ")";
        return out;
    }
}
