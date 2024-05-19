#include "Point.h"
#include "InputFormatters.h"

std::istream& operator>>(std::istream& in, Point& point)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  Point tmp;
  in >> DelimiterI{ '(' } >> tmp.x >> DelimiterI{ ';' } >> tmp.y >> DelimiterI{ ')' };
  if (!in.fail())
  {
    point = tmp;
  }
  return in;
}

bool Point::operator==(const Point& other) const
{
  return (x == other.x) && (y == other.y);
}
