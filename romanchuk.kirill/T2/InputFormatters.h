#ifndef READER_H
#define READER_H

#include "DataStruct.h"


struct DelimiterI
{
  char exp;
};

struct DoubleI
{
  double& ref;
};

struct StringI
{
  std::string& ref;
};

struct LabelI
{
  std::string& ref;
};

struct LongLongI
{
  unsigned long long& num;
};

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::istream& operator>>(std::istream& in, DelimiterI&& dest);
std::istream& operator>>(std::istream& in, DoubleI&& dest);
std::istream& operator>>(std::istream& in, StringI&& dest);
std::istream& operator>>(std::istream& in, LabelI&& dest);
std::istream& operator>>(std::istream& in, LongLongI&& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

#endif
