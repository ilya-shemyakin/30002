#ifndef POLIGON_H
#define POLIGON_H

#include<vector>
#include"Point.h"

struct Polygon
{
  std::vector< Point > points_arr;
  bool operator==(const Polygon& right) const;
};

std::istream& operator>>(std::istream& in, Polygon& polygon);

#endif
