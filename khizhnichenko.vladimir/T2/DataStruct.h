#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <string>

namespace khizhnichenko {
  struct DataStruct {
    long long key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
  };

  bool operator<(const DataStruct& rhs, const DataStruct& lhs);
  std::istream& operator>>(std::istream& in, DataStruct& dest);
  std::ostream& operator<<(std::ostream& out, const DataStruct& dest);
}

#endif
