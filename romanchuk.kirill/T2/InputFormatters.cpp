#include "InputFormatters.h"

#include <sstream>
#include <iomanip>
#include <execution>

#include "StreamGuard.h"


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

std::istream& operator>>(std::istream& in, DelimiterI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (std::tolower(c) != dest.exp))
  {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, DoubleI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return in >> dest.ref >> DelimiterI{ 'd' };
}

std::istream& operator>>(std::istream& in, StringI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in, dest.ref, ' ');
}

std::istream& operator>>(std::istream& in, LongLongI&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  in >> DelimiterI{ '0' } >> DelimiterI{ 'x' };
  std::string data = "";
  std::getline(in, data, ':');
  in.putback(':');
  size_t pos = 0;
  unsigned long long num = 0;
  bool conversion_successful = true;
  if (!data.empty())
  {
    try
    {
      num = std::stoull(data, &pos, 16);
    }
    catch (const std::exception& ex)
    {
      conversion_successful = false;
    }
  }
  else
  {
    conversion_successful = false;
  }
  if (pos != data.size() || !conversion_successful)
  {
    in.setstate(std::ios::failbit);
  }
  else
  {
    dest.num = num;
  }
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
  out << "key2 " << dest.key2 << ":";
  out << "key3 \"" << dest.key3 << "\"";
  out << ":)";
  return out;
}
