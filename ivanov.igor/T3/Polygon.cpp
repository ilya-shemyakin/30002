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
    std::istream& operator>>(std::istream& in, Polygon& poly)
    {
        std::istream::sentry guard(in);
        if (!guard)
        {
            return in;
        }
        size_t size;
        in >> size;
        if (size < 3)
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        poly.points.clear();
        poly.points.resize(size);

        for (size_t i = 0; i < size; i++)
        {
            in >> poly.points[i];
        }

        if (in.peek() != int('\n') && !in.eof())
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        return in;
    }


    std::ostream& operator<<(std::ostream& out, const Polygon& poly)
    {
        std::ostream::sentry guard(out);
        if (!guard)
        {
            return out;
        }
        out << poly.points.size() << " ";
        for (const auto& p : poly.points)
        {
            out << p << " ";
        }
        return out;
    }
}
