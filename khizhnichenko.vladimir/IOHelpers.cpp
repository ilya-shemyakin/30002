
#include "IOHelpers.h"

namespace khizhnichenko
{
  iofmtguard::iofmtguard(std::basic_ios< char >& s) :
      s_(s),
      fill_(s.fill()),
      precision_(s.precision()),
      fmt_(s.flags())
  {}

  iofmtguard::~iofmtguard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }

  std::istream& operator>>(std::istream& in, const ExpectedCharIO&& exp)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }

    char c = in.get();
    bool isExpected = exp.ignoreCase ? (std::tolower(c) == std::tolower(exp.val)) : (c == exp.val);
    if (in && !isExpected)
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }
}
