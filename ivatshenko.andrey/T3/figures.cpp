#include "figures.h"

bool ivatshenko::Point::operator<(const Point& right)
{
    return (this->x < right.x) || ((this->x == right.x) && (this->y < right.y));
}

bool ivatshenko::Point::operator==(const Point& right)
{
    return this->x == right.x && this->y == right.y;
}

double ivatshenko::getDistance(const Point& p1, const Point& p2)
{
    return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
}

double ivatshenko::Polygon::getArea() const
{
    Point fixed = points[0], first = points[1];
    double square = std::accumulate(
        points.begin() + 2,
        points.end(),
        0.0,
        [fixed, &first](double accumulator, Point second)
        {
            accumulator += Triangle(fixed, first, second).getArea();
            first = second;
            return accumulator;
        }
    );
    return square;
}

bool ivatshenko::Polygon::operator==(const Polygon& right)
{
    std::vector<Point> vec1 = this->points;
    std::vector<Point> vec2 = right.points;
    if (vec1.size() != vec2.size())
    {
        return false;
    }
    std::sort(vec1.begin(), vec1.end());
    std::sort(vec2.begin(), vec2.end());
    bool result = true;
    std::size_t i = 0;
    while (i < vec1.size() && result)
    {
        result = result && (vec1[i] == vec2[i]);
        i += 1;
    }
    return result;
}

ivatshenko::Frame ivatshenko::getFrame(const std::vector<Polygon>& data)
{
    if (data.size() == 0)
    {
        throw std::runtime_error("<TOO FEW POLYGONS>");
    }
    Point lowerLeft = data[0].points[0];
    Point upperRight = data[0].points[0];
    for (const Polygon& poly : data)
    {
        for (const Point& p : poly.points)
        {
            if (p.x < lowerLeft.x)
            {
                lowerLeft.x = p.x;
            }
            if (p.x > upperRight.x)
            {
                upperRight.x = p.x;
            }
            if (p.y < lowerLeft.y)
            {
                lowerLeft.y = p.y;
            }
            if (p.y > upperRight.y)
            {
                upperRight.y = p.y;
            }
        }
    }
    return Frame(lowerLeft, upperRight);
}

ivatshenko::Triangle::Triangle(const Point& a, const Point& b, const Point& c) :
    a(a),
    b(b),
    c(c)
{}

double ivatshenko::Triangle::getArea() const
{
    double x = getDistance(a, b);
    double y = getDistance(a, c);
    double z = getDistance(b, c);
    double p = (x + y + z) / 2;
    return std::sqrt(p * (p - x) * (p - y) * (p - z));
}

ivatshenko::Frame::Frame(const Point& lowerLeft, const Point& upperRight)
{
    if (lowerLeft.x > upperRight.x || lowerLeft.y > upperRight.y)
    {
        throw std::invalid_argument("Invalid frame");
    }
    this->lowerLeft = lowerLeft;
    this->upperRight = upperRight;
}

bool ivatshenko::Frame::containsPoint(const Point& p) const
{
    return p.x >= lowerLeft.x && p.x <= upperRight.x && p.y >= lowerLeft.y && p.y <= upperRight.y;
}

bool ivatshenko::Frame::containsPolygon(const Polygon& poly) const
{
    return std::all_of(
        poly.points.begin(),
        poly.points.end(),
        [this](const Point& p)
        {
            return containsPoint(p);
        }
    );
}
