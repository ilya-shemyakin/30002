#include "Delimeter.h"

std::istream & IO::operator>>(std::istream & is, IO::Delimiter && exp)
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