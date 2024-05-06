#include "Keys.h"
#include "Delimeter.h"
#include "ScopeGuard.h"

std::istream & IO::operator>>(std::istream & is, IO::ULLOCT && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  is >> del{'0'};
  return is >> std::oct >> value.num;
}

std::istream & operator>>(std::istream & is, IO::CMPLSP && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  using del = Delimiter;
  double real;
  double imag;
  is >> del{'#'} >> del{'c'} >> del{'('} >> real >> imag >> del{')'};
  value.num.real(real);
  value.num.imag(imag);
  return is;
}

std::istream & operator>>(std::istream & is, IO::STR && value)
{
  std::istream::sentry sentry(is);
  if (!sentry)
  {
    return is;
  }
  return std::getline(is >> Delimiter{ '"' }, value.num, '"');
}