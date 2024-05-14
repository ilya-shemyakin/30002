#ifndef IOHELPERS_H
#define IOHELPERS_H

#include <iostream>

namespace maltsev
{
  class iofmtguard
  {
  public:
    iofmtguard(std::basic_ios<char>& s);
    ~iofmtguard();
  private:
    std::basic_ios<char>& s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios<char>::fmtflags fmt_;
  };

  struct ExpectedCharIO
  {
    const char& val;
    bool ignoreCase = false;
  };

  std::istream& operator>>(std::istream& in, const ExpectedCharIO&& exp);
}

#endif
