#ifndef Delimeter_h
#define Delimeter_h
#include <iostream>

namespace bolatbek
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, bolatbek::Delimiter && exp);
}

#endif