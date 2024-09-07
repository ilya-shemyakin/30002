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
  double square =
    std::accumulate(points.begin() + 2, points.end(), 0.0, [fixed, &first](double accumulator, Point second) {
      accumulator += Triangle(fixed, first, second).getArea();
      first = second;
      return accumulator;
    });
  return square;
}

bool ivatshenko::Polygon::operator==(const Polygon& right) const
{
  std::vector< Point > vec1 = this->points;
  std::vector< Point > vec2 = right.points;
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

ivatshenko::Frame ivatshenko::getFrame(const std::vector< Polygon >& data)
{
  if (data.empty())
  {
    throw std::runtime_error("<INVALID ARGUMENT>");
  }

  auto compareX = [](const Point& p1, const Point& p2) { return p1.x < p2.x; };
  auto compareY = [](const Point& p1, const Point& p2) { return p1.y < p2.y; };

  auto minX = std::min_element(data.begin(), data.end(), [&compareX](const Polygon& a, const Polygon& b) {
    return std::min_element(a.points.begin(), a.points.end(), compareX)->x <
           std::min_element(b.points.begin(), b.points.end(), compareX)->x;
  });
  auto maxX = std::max_element(data.begin(), data.end(), [&compareX](const Polygon& a, const Polygon& b) {
    return std::max_element(a.points.begin(), a.points.end(), compareX)->x <
           std::max_element(b.points.begin(), b.points.end(), compareX)->x;
  });

  auto minY = std::min_element(data.begin(), data.end(), [&compareY](const Polygon& a, const Polygon& b) {
    return std::min_element(a.points.begin(), a.points.end(), compareY)->y <
           std::min_element(b.points.begin(), b.points.end(), compareY)->y;
  });
  auto maxY = std::max_element(data.begin(), data.end(), [&compareY](const Polygon& a, const Polygon& b) {
    return std::max_element(a.points.begin(), a.points.end(), compareY)->y <
           std::max_element(b.points.begin(), b.points.end(), compareY)->y;
  });

  Point lowerLeft = { std::min_element(minX->points.begin(), minX->points.end(), compareX)->x,
                      std::min_element(minY->points.begin(), minY->points.end(), compareY)->y };

  Point upperRight = { std::max_element(maxX->points.begin(), maxX->points.end(), compareX)->x,
                       std::max_element(maxY->points.begin(), maxY->points.end(), compareY)->y };

  return Frame(lowerLeft, upperRight);
}

ivatshenko::Triangle::Triangle(const Point& a, const Point& b, const Point& c):
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
  return std::all_of(poly.points.begin(), poly.points.end(), [this](const Point& p) { return containsPoint(p); });
}
