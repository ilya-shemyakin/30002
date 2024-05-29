#ifndef FIGURES_H
#define FIGURES_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>

namespace ivatshenko
{
  struct Point
  {
    int x, y;
    bool operator<(const Point& right);
    bool operator==(const Point& right);
  };

  double getDistance(const Point& p1, const Point& p2);

  std::ostream& operator<<(std::ostream& out, const Point& point);

  struct Polygon
  {
    std::vector< Point > points;
    double getArea() const;
    bool operator==(const Polygon& right) const;
    bool operator<(const Polygon& right);
  };

  struct Triangle
  {
    Point a, b, c;
    Triangle(const Point& a, const Point& b, const Point& c);
    double getArea() const;
  };

  struct Frame
  {
    Point lowerLeft;
    Point upperRight;
    Frame(const Point& lowerLeft, const Point& upperRight);
    bool containsPoint(const Point& p) const;
    bool containsPolygon(const Polygon& poly) const;
  };
  Frame getFrame(const std::vector< Polygon >& data);
}
#endif
