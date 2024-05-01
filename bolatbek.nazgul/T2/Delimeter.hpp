#ifndef Delimeter_hpp
#define Delimeter_hpp
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