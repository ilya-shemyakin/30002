#ifndef INPUT_FORMAT_H
#define INPUT_FORMAT_H
#include<iostream>
#include<complex>

struct DelimiterIO {
  char exp;
};

struct LabelIO {
  std::string& exp;
};

struct StringIO {
  std::string& ref;
};

struct LongLongIO {
  unsigned long long& val;
};

struct CmpLspIO {
  std::complex<double>& cmp;
};

std::istream& operator>>(std::istream& in, LabelIO&& dest);
std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, StringIO&& dest);
std::istream& operator>>(std::istream& in, LongLongIO&& dest);
std::istream& operator>>(std::istream& in, CmpLspIO&& dest);

#endif
