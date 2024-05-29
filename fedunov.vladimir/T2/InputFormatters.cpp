#include "InputFormatters.h"

std::istream& operator>>(std::istream& in, DelimiterI&& dest)
{
  char c;
  in >> c;
  if (in && c != dest.exp)
    in.setstate(std::ios::failbit);
  return in;
}

std::istream& operator>>(std::istream& in, DoubleI&& dest)
{
  return in >> dest.ref >> DelimiterI{ 'd' };
}

std::istream& operator>>(std::istream& in, StringI&& dest)
{
  return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LabelI&& dest)
{
  return std::getline(in, dest.ref, ' ');
}

std::istream& operator>>(std::istream& in, LongLongI&& dest)
{
  char x;
  in >> DelimiterI{ '0' } >> x;
  if (in && x != 'x')
    in.setstate(std::ios::failbit);
  else
    in >> std::hex >> dest.num;
  return in;
}
