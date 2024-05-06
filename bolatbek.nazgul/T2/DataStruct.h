#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <string>
#include "Keys.h"

namespace IO
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