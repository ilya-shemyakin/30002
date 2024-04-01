#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

namespace maltsev
{
  struct DataStruct
  {
    unsigned long long key1;
    unsigned long long key2;
    std::string key3;
  };

  bool operator<(DataStruct& rhs, DataStruct& lhs);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif