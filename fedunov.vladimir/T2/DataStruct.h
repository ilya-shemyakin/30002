#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>
#include <string>

struct DataStruct
{
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3;
};

bool operator<(const DataStruct& lhs, const DataStruct& rhs);
std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

#endif