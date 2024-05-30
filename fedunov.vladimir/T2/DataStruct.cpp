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
  std::string line;
  if (!std::getline(in, line))
    return in;

  std::istringstream iss(line);
  DataStruct input;
  using sep = DelimiterI;
  using label = LabelI;
  using dbl = DoubleI;
  using str = StringI;
  using num = LongLongI;

  char ch;
  iss >> ch;
  if (ch != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  bool key1_parsed = false, key2_parsed = false, key3_parsed = false;
  for (size_t i = 0; i < 3; ++i)
  {
    std::string key;
    if (!(iss >> sep{ ':' } >> label{ key }))
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    if (key == "key1")
    {
      if (!(iss >> dbl{ input.key1 }))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      key1_parsed = true;
    }
    else if (key == "key2")
    {
      if (!(iss >> num{ input.key2 }))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      key2_parsed = true;
    }
    else if (key == "key3")
    {
      if (!(iss >> str{ input.key3 }))
      {
        in.setstate(std::ios::failbit);
        return in;
      }
      key3_parsed = true;
    }
    else
    {
      in.setstate(std::ios::failbit);
      return in;
    }
  }

  if (!(iss >> sep{ ':' } >> ch) || ch != ')')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!iss.fail() && key1_parsed && key2_parsed && key3_parsed)
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
