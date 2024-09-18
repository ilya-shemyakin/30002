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

    bool Polygon::isCompatibleWith(const Polygon& other) const
    {
        if (points.size() != other.points.size())
        {
            return false;
        }

        auto translate = [](const std::vector<Point>& poly, const Point& offset) {
            std::vector<Point> translatedPoly;
            translatedPoly.reserve(poly.size());
            for (const auto& p : poly) {
                translatedPoly.push_back({ p.x - offset.x, p.y - offset.y });
            }
            return translatedPoly;
        };

        auto sortPoints = [](std::vector<Point>& poly) {
            std::sort(poly.begin(), poly.end(), [](const Point& a, const Point& b) {
                return std::tie(a.x, a.y) < std::tie(b.x, b.y);
            });
        };

        auto arePolygonsEqual = [](const std::vector<Point>& poly1, const std::vector<Point>& poly2) {
            return poly1 == poly2;
        };

        std::vector<Point> poly1 = points;
        std::vector<Point> poly2 = other.points;

        sortPoints(poly1);

        // Try all possible translations of poly2
        for (const auto& p : poly2)
        {
            std::vector<Point> translatedPoly = translate(poly2, p);
            sortPoints(translatedPoly);

            if (arePolygonsEqual(poly1, translatedPoly))
            {
                return true;
            }
        }

        return false;
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
