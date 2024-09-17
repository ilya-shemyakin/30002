#include "Point.h"
#include "InputFormatters.h"

std::istream& operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  Point t;
  in >> Delimeter{ '(' } >> t.x >> Delimeter{ ';' } >> t.y >> Delimeter{ ')' };
  if (!in.fail()) {
    point = t;
  }
  return in;
}

bool Point::operator==(const Point& right) const
{
  return (this->x == right.x) && (this->y == right.y);
}
