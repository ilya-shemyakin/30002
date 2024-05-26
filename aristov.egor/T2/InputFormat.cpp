#include "InputFormat.h"
#include"StreamGuard.h"
#include <iomanip>
#include <string>


std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in, dest.exp, ' ');
}

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  char c = '0';
  in >> c;
  if (in && (c != dest.exp)) {
    in.setstate(std::ios::failbit);
  }
  return in;
}

std::istream& operator>>(std::istream& in, StringIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LongLongIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  StreamGuard guard(in);
  in >> DelimiterIO{ '0' } >> DelimiterIO{ 'x' };
  return in >> std::hex >> dest.val;
}

std::istream& operator>>(std::istream& in, CmpLspIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  StreamGuard guard(in);
  in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' };
  double tempVal1 = 0;
  in >> tempVal1;
  if (!in) {
    return in;
  }
  double tempVal2 = 0;
  in >> tempVal2;
  in >> DelimiterIO{ ')' };
  if (in) {
    dest.cmp = std::complex<double>(tempVal1, tempVal2);
  }
  return in;
}
