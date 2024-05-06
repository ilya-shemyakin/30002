#ifndef Delimeter_h
#define Delimeter_h
#include <iostream>

namespace IO
{
  struct Delimiter
  {
    char expected;
  };
  std::istream & operator>>(std::istream & is, IO::Delimiter && exp);
}

#endif