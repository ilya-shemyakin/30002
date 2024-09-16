#include "InputFormat.h"
#include "StreamGuard.h"
#include <iomanip>
#include <cctype>
#include <sstream>

namespace fedunov {
  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    StreamGuard guard(in);
    return in >> dest.ref >> LabelIO{ "ull", true };
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    return in >> std::quoted(dest.ref);
  }

  std::istream& operator>>(std::istream& in, DelimiterIO dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != dest.exp))
    {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    char c = '0';
    for (size_t i = 0; i < dest.val.size(); ++i)
    {
      c = in.get();
      if (in && (c != dest.val[i]))
      {
        in.setstate(std::ios::failbit);
        break;
      }
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, ComplexIO&& dest)
  {
    using del = DelimiterIO;

    std::istream::sentry sentry(in);
    if (!sentry) return in;

    StreamGuard guard(in);

    char c;
    double real_part = 0.0,
      imag_part = 0.0;

    in >> std::fixed;
    in >> del{ '#' } >> del{ 'c' } >> del{ '(' } >>
      real_part >> del{ ' ' } >> imag_part >> del{ ')' };

    dest.ref.real(real_part);
    dest.ref.imag(imag_part);

    return in;
  }
}
