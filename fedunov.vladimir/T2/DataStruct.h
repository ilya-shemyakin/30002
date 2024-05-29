#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

struct DataStruct
{
  double key1 = 0;
  std::string key1_str;
  unsigned long long key2 = 0;
  std::string key2_str;
  std::string key3;
};

bool operator<(const DataStruct& lhs, const DataStruct& rhs);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

#endif
