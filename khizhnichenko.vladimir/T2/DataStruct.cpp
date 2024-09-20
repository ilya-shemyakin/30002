#include <iomanip>
#include <istream>
#include <set>

#include "DataStruct.h"
#include "InputAdapters.h"
#include "StreamGuard.h"

namespace khizhnichenko {
  bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) {
      return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2) {
      return (lhs.key2.first / lhs.key2.second) < (rhs.key2.first / rhs.key2.second);
    }
    return lhs.key3.length() < rhs.key3.length();
  }

  std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    DataStruct input{ 0, {0, 0}, "" }; {
      iofmtguard fmtguard(in);
      using ll = LongLongIO;
      using rn = RationalNumberIO;
      using str = StringIO;
      using chr = ExpectedCharIO;
      using label = LabelIO;
      constexpr std::size_t FIELDS_COUNT = 3;
      int keyId = 0;
      in >> chr{ '(' };
      for (size_t i = 0; i < FIELDS_COUNT; i++) {
        in >> label{ ":key" } >> keyId;
        if (keyId == 1) {
          in >> ll{ input.key1 };
        }
        else if (keyId == 2) {
          in >> rn{ input.key2 };
        }
        else if (keyId == 3) {
          in >> str{ input.key3 };
        }
        else {
          in.setstate(std::istream::failbit);
          break;
        }
      }
      in >> label{ ":)" };
    }
    if (in) {
      dest = input;
    }
    return in;
  }

  std::ostream& operator<<(std::ostream& out, const DataStruct& src) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
      return out;
    }

    iofmtguard fmtguard(out);
    out << "(:";
    out << "key1 " << src.key1 << "ll" << ":";
    out << "key2 " << "(:N " << src.key2.first << ":D " << src.key2.second << ":)" << ":";
    out << "key3 " << std::quoted(src.key3) << ":";
    out << ")";
    return out;
  }
}
