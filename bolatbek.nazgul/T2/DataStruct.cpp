#include "DataStruct.h"
#include <iostream>
#include "Delimeter.h"
#include "Keys.h"
#include "ScopeGuard.h"

bool operator<(const IO::DataStruct & first, const DataStruct & second)
{
  if (first.key1 != second.key1)
  {
    return (first.key1 < second.key1);
  }
  else if (first.key2 != second.key2)
  {
    return (abs(first.key2) < abs(second.key2));
  }
  else
  {
    return (first.key3.length() < second.key3.length());
  }
}

std::istream & operator>>(std::istream & is, DataStruct & value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  std::string key = "";
  DataStruct data_struct;
  is >> del{'('} >> del{':'};
  for (size_t i = 1; i <= 3; i++)
  {
    is >> key;
    if (key == "key1")
    {
      is >> ULLOCT{data_struct.key1} >> del{':'};
    }
    else if (key == "key2")
    {
      is >> CMPLSP{data_struct.key2} >> del{':'};
    }
    else
    {
      is >> STR{data_struct.key3} >> del{':'};
    }
  }
  is >> del{')'};
  if (is)
  {
    value = data_struct;
  }
  return is;
}

std::ostream & operator<<(std::ostream & out, const DataStruct & value)
{
  std::ostream::sentry sentry(out);
  iofmtguard guard(out);
  if(!sentry)
  {
    return out;
  }
  out << "(:" << "key1 0" << std::oct << value.key1;
  out << ":" << std::fixed << "key2 #c(" << std::setprecision(1) << value.key2.real();
  out << " " << value.key2.imag() << ")";
  out << ":" << std::fixed << "key3 \"" << value.key3 << "\":)";
  return out;
}
