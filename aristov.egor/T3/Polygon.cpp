#include "Polygon.h"
#include<algorithm>

std::istream& operator>>(std::istream& in, Polygon& polygon)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  size_t pts_count;
  in >> pts_count;
  if (pts_count < 3) {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector< Point > t_arr;
  std::generate_n(std::back_inserter(t_arr), pts_count, [&in]() {
    Point t_point;
    in >> t_point;
    return t_point;
    });
  if (!in.fail()) {
    polygon.points_arr = t_arr;
    polygon.points_arr.shrink_to_fit();
  }
  return in;
}

bool Polygon::operator==(const Polygon& right) const
{
  return this->points_arr == right.points_arr;
}
