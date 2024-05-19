#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
  int x, y;
  bool operator==(const Point& other) const;
};

std::istream& operator>>(std::istream& in, Point& point);

#endif // !POINT_H
