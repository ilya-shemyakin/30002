#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>


struct DataStruct
{
  double key1 = 0;
  unsigned long long key2 = 0;
  std::string key3; 

  DataStruct& operator=(const DataStruct& other)
  {
    if (this != &other)
    {
      key1 = other.key1;
      key2 = other.key2;
      key3 = other.key3;
    }
    return *this;
  }

  bool operator<(const DataStruct& other) const
  {
    if (key1 < other.key1)
    {
      return true;
    }
    else if (key1 == other.key1)
    {
      if (key2 < other.key2)
      {
        return true;
      }
      else if (key2 == other.key2)
      {
        return key3 < other.key3;
      }
      return false;
    }
    return false;
  }

  bool operator>(const DataStruct& other) const
  {
    return !(*this < other);
  }
};

#endif
