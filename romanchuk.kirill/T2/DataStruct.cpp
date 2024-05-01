#include "DataStruct.h"

#include <sstream>
#include <iomanip>
#include <execution>

#include "InputFormatters.h"
#include "StreamGuard.h"


bool operator<(DataStruct& lhs, DataStruct& rhs)
{
  if (lhs.key1 < rhs.key1)
  {
    return true;
  }
  else if (lhs.key1 == rhs.key1)
  {
    if (lhs.key2 < rhs.key2)
    {
      return true;
    }
    else if (lhs.key2 == rhs.key2)
    {
      return lhs.key3 < rhs.key3;
    }
    return false;
  }
  return false;
}

std::istream& operator>>(std::istream& in, DataStruct& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterI;
    using label = LabelI;
    using dbl = DoubleI;
    using str = StringI;
    using num = LongLongI;
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++)
    {
      std::string key;
      in >> sep{ ':' } >> label{ key };
      if (key == "key1")
      {
        in >> dbl{ input.key1 };
      }
      else if (key == "key2")
      {
        in >> num{ input.key2 };
      }
      else if (key == "key3")
      {
        in >> str{ input.key3 };
      }
      else
      {
        in.setstate(std::ios::failbit);
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
  }
  if (!in)
  {
    in.setstate(std::ios::failbit);
  }
  dest = input;
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  StreamGuard guard(out);
  out << "(:";
  out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "d:";
  out << "key2 0x" << std::hex << std::uppercase << dest.key2 << ":";
  out << "key3 \"" << dest.key3 << "\"";
  out << ":)";
  return out;
}
