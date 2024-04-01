#pragma once
#include <istream>
#include <string>

namespace maltsev
{
  struct UnsignedLongLongIO
  {
    unsigned long long& ref;
  };

  struct UnsignedLongLongHexIO
  {
    unsigned long long& ref;
  };

  struct StringIO
  {
    std::string& ref;
  };

  struct ExpectedCharIO
  {
    const char& val;
    bool ignoreCase = false;
  };

  struct LabelIO
  {
    const std::string& val;
    bool ignoreCase = false;
  };

  std::istream& operator>>(std::istream& in, UnsignedLongLongIO&& dest);
  std::istream& operator>>(std::istream& in, UnsignedLongLongHexIO&& dest);
  std::istream& operator>>(std::istream& in, StringIO&& dest);
  std::istream& operator>>(std::istream& in, ExpectedCharIO&& exp);
  std::istream& operator>>(std::istream& in, LabelIO&& exp);
}
