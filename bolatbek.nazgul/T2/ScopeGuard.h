#ifndef SCOPEGUARD_H
#define SCOPEGUARD_H

#include <iomanip>

namespace bolatbek
{
  class iofmtguard
  {
  public:
    explicit iofmtguard(std::basic_ios< char > &s) noexcept;
    ~iofmtguard();
  private:
    std::basic_ios< char > &s_;
    char fill_;
    std::streamsize precision_;
    std::basic_ios< char >::fmtflags fmt_;
  };
}

#endif