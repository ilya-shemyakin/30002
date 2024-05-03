#ifndef KEYS_H
#define KEYS_H
#include <string>
#include <complex>
#include <iosfwd>

namespace bolatbek
{
  struct ULLOCT
  {
    unsigned long long int & num;
  };

  struct CMPLSP
  {
    std::complex< double > & num;
  };

  struct STR
  {
    std::string & num;
  };

  std::istream & operator>>(std::istream & is, ULLOCT && value);
  std::istream & operator>>(std::istream & is, CMPLSP && value);
  std::istream & operator>>(std::istream & is, STR && value);
  std::ostream & operator<<(std::ostream & out, const ULLOCT && value);
}
#endif