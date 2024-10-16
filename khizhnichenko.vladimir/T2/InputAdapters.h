#ifndef INPUT_ADAPTERS_H
#define INPUT_ADAPTERS_H

#include <istream>
#include <string>

namespace khizhnichenko {
  struct LongLongIO {
    long long& ref;
  };

  struct RationalNumberIO {
    std::pair<long long, unsigned long long>& ref;
  };

  struct StringIO {
    std::string& ref;
  };

  struct ExpectedCharIO {
    const char& val;
    bool ignoreCase = false;
  };

  struct LabelIO {
    const std::string& val;
    bool ignoreCase = false;
  };

  std::istream& operator>>(std::istream& in, LongLongIO&& dest);
  std::istream& operator>>(std::istream& in, RationalNumberIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, ExpectedCharIO&& exp);
  std::istream& operator>>(std::istream& in, LabelIO&& exp);
}

#endif
