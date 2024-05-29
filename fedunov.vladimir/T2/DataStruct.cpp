#include "DataStruct.h"
#include "InputFormatters.h"
#include "StreamGuard.h"
#include <iomanip>
#include <sstream>

bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
    return lhs.key1 < rhs.key1;
  if (lhs.key2 != rhs.key2)
    return lhs.key2 < rhs.key2;
  return lhs.key3.length() < rhs.key3.length();
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
    return in;

  DataStruct input;
  using sep = DelimiterI;
  using label = LabelI;
  using dbl = DoubleI;
  using str = StringI;
  using num = LongLongI;

  char ch;
  in >> ch;
  if (ch != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  bool key1_parsed = false, key2_parsed = false, key3_parsed = false;
  for (size_t i = 0; i < 3; ++i)
  {
    std::string key;
    in >> sep{ ':' } >> label{ key };
    if (key == "key1")
    {
      if (!(in >> dbl{ input.key1 }))
      {
        in.clear();
        in >> str{ input.key1_str };
      }
      key1_parsed = true;
    }
    else if (key == "key2")
    {
      if (!(in >> num{ input.key2 }))
      {
        in.clear();
        in >> str{ input.key2_str };
      }
      key2_parsed = true;
    }
    else if (key == "key3")
    {
      in >> str{ input.key3 };
      key3_parsed = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  in >> sep{ ':' } >> ch;
  if (ch != ')')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (key1_parsed && key2_parsed && key3_parsed && !in.fail())
    dest = input;

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
    return out;

  StreamGuard guard(out);
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d:";
  out << "key2 0x" << std::hex << std::uppercase << dest.key2 << ":";
  out << "key3 \"" << dest.key3 << "\"";
  out << ":)";
  return out;
}
