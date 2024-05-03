#ifndef POINT_H
#define POINT_H

#include <iostream>

struct Point
{
  int x, y;
};

std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Point& point);

#endif // !POINT_H
