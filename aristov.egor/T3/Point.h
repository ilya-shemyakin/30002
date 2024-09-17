#ifndef POINT_H
#define POINT_H

#include<iostream>

struct Point
{
  int x, y;
  bool operator==(const Point& right) const;
};

std::istream& operator>>(std::istream& in, Point& point);

#endif
