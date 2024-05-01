#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>
#include "Keys.hpp"

namespace bolatbek
{
  struct DataStruct
  {
    unsigned long long key1;
    std::complex< double > key2;
    std::string key3;
  };
  bool operator<(const DataStruct & first, const DataStruct & second);
  std::istream & operator>>(std::istream & is, DataStruct & value);
  std::ostream & operator<<(std::ostream & out, const DataStruct & value);
}
#endif