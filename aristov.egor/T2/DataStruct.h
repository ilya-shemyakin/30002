#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include<iostream>
#include<complex>

struct DataStruct
{
  unsigned long long key1 = 0;
  std::complex<double> key2 = 0;
  std::string key3;
};

bool operator<(const DataStruct& left, const DataStruct& right);

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);
std::istream& operator>>(std::istream& in, DataStruct& dataStruct);

#endif
