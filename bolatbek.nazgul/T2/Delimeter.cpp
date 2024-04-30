#include "Delimeter.hpp"

std::istream & bolatbek::operator>>(std::istream & is, bolatbek::Delimiter && exp)
{
  std::istream::sentry guard(is);
  if (!guard)
  {
    return is;
  }
  char c = 0;
  is >> c;
  if (c != exp.expected)
  {
    is.setstate(std::ios::failbit);
  }
  return is;
}
