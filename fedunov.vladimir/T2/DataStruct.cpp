#include "DataStruct.h"
#include "InputFormat.h"
#include "StreamGuard.h"
#include <iomanip>
#include <sstream>
#include <iostream>

namespace fedunov {

  bool operator<(const DataStruct& lhs, const DataStruct& rhs)
  {
    if (lhs.key1 != rhs.key1)
    {
      return lhs.key1 < rhs.key1;
    }
    if (std::abs(lhs.key2) != std::abs(rhs.key2))
    {
      return std::abs(lhs.key2) < std::abs(rhs.key2);
    }

    return lhs.key3.length() < rhs.key3.length();
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest)
  {
    std::istream::sentry sentry(in);
    if (!sentry) return in;

    DataStruct input;
    StreamGuard guard(in);
    in >> std::noskipws;

    if (!(in >> DelimiterIO{ '(' }))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    const int KEY_NUMBER = 3;
    for (int i = 1; i <= KEY_NUMBER; ++i)
    {
      if (!(in >> DelimiterIO{ ':' } >> LabelIO{ "key" }))
      {
        in.setstate(std::ios::failbit);
        return in;
      }

      char keyNumber = in.get();
      in >> DelimiterIO{ ' ' };

      switch (keyNumber)
      {
      case '1':
        if (!(in >> UnsignedLongLongIO{ input.key1 }))
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        break;

      case '2':
        if (!(in >> ComplexIO{ input.key2 }))
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        break;

      case '3':
        if (!(in >> StringIO{ input.key3 }))
        {
          in.setstate(std::ios::failbit);
          return in;
        }
        break;

      default:
        in.setstate(std::ios::failbit);
        return in;
      }
    }

    if (!(in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' }))
    {
      in.setstate(std::ios::failbit);
      return in;
    }

    if (in)
    {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src)
  {

    std::ostream::sentry sentry(out);
    if (!sentry)
    {
      return out;
    }

    StreamGuard guard(out);

    out << "(:";
    out << "key1 " << std::fixed << src.key1 << "ull:";
    out << "key2 #c(" << std::setprecision(1) << src.key2.real() << " " << std::setprecision(1) << src.key2.imag() << "):";
    out << "key3 " << std::quoted(src.key3);
    out << ":)";

    return out;
  }
}
