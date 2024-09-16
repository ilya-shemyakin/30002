#ifndef INPUT_FORMATS_H
#define INPUT_FORMATS_H

#include <complex>
#include <string>
#include <istream>

namespace fedunov {
  struct UnsignedLongLongIO {
    unsigned long long& ref;
  };

  struct ComplexIO {
    std::complex<double>& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  struct LabelIO {
    const std::string& val;
    bool ignoreCase = true;
  };

  struct DelimiterIO {
    char exp;
  };

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, ComplexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, DelimiterIO dest);
  std::istream& operator>>(std::istream& in, LabelIO&& exp);
}

#endif
