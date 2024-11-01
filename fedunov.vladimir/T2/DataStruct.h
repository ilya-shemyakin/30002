#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <iostream>
#include <complex>
#include <string>

namespace fedunov {
  struct DataStruct
  {
    unsigned long long key1;
    std::complex<double> key2;
    std::string key3;
  };

  bool operator<(const DataStruct& lhs, const DataStruct& rhs);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& src);
}

#endif
