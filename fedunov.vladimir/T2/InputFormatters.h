#ifndef INPUTFORMATTERS_H
#define INPUTFORMATTERS_H

#include <iostream>
#include <string>

struct DelimiterI
{
  char exp;
};

struct LongLongI
{
  unsigned long long& num;
};

struct StringI
{
  std::string& ref;
};

struct LabelI
{
  std::string& ref;
};

std::istream& operator>>(std::istream& in, DelimiterI&& dest);
std::istream& operator>>(std::istream& in, LongLongI&& dest);
std::istream& operator>>(std::istream& in, StringI&& dest);
std::istream& operator>>(std::istream& in, LabelI&& dest);

#endif
