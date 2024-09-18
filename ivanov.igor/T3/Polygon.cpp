#include <algorithm>
#include <functional>
#include <numeric>
#include <iterator>

#include "IOHelpers.h"
#include "Polygon.h"
#include "Functors.h"

namespace ivanov
{
    double Polygon::computeArea() const
    {
        using namespace std::placeholders;
        auto acc_area = std::bind(AccumulatePolygonArea{ points[1] }, _1, _2, points[0]);
        return std::accumulate(points.cbegin(), points.cend(), 0.0, acc_area);
    }

    bool Polygon::operator==(const Polygon& other) const
    {
        if (points.size() != other.points.size())
        {
            return false;
        }
        return (std::mismatch(points.cbegin(), points.cend(),
            other.points.cbegin())
            .first == points.cend());
    }

    bool Polygon::is_overlay_compatible(const Polygon& other) const
    {
        if (points.size() != other.points.size()) return false;

        std::vector<Point> sorted_points(points);
        std::sort(sorted_points.begin(), sorted_points.end());

        double x_offset = other.points[0].x - sorted_points[0].x;
        double y_offset = other.points[0].y - sorted_points[0].y;

        auto sorted_pnt = sorted_points.begin();
        auto testFunc = [&sorted_pnt, &x_offset, &y_offset](const Point& pnt)
            {
                bool result = pnt.x - (*sorted_pnt).x == x_offset && pnt.y - (*sorted_pnt).y == y_offset;
                sorted_pnt++;
                return result;
            };

        return std::all_of(other.points.begin(), other.points.end(), testFunc);
    }
    std::istream& operator>>(std::istream& in, Polygon& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        int size = 0;
        in >> size;
        if (size < 3)
        {
            in.setstate(std::istream::failbit);
            return in;
        }
        std::vector<Point> tempPoints;
        tempPoints.reserve(size);
        std::copy_n(std::istream_iterator<Point>(in), size, std::back_inserter(tempPoints));

        if (in)
        {
            dest.points = tempPoints;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const Polygon& polygon)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }

        std::copy(polygon.points.cbegin(), polygon.points.cend(),
            std::ostream_iterator<Point>(out, " "));
        return out;
    }
}
