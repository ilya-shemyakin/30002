#include <iomanip>

#include "InputAdapters.h"
#include "StreamGuard.h"

namespace khizhnichenko {
  std::istream& operator>>(std::istream& in, LongLongIO&& dest) {
    // Проверка состояния потока.
    // Необходима в начале каждого переопределения operator>>
    std::istream::sentry sentry(in);
    if (!sentry)
    {
      return in;
    }
    iofmtguard fmtguard(in);
    /*
    [SLL LIT] (long long):
      :keyX 89ll:
      :keyX -89LL:
    */
    return in >> dest.ref >> LabelIO{ "ll", true };
  }

  std::istream& operator>>(std::istream& in, RationalNumberIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    iofmtguard fmtguard(in);
    /*
    [RAT LSP] (std::pair<long long, unsigned long long > ):
      :keyX (:N -2:D 3:):
      :keyX (:N 3:D 2:):
    */
    
    return in >> LabelIO{ "(:N " } >> dest.ref.first
              >> LabelIO{ ":D " } >> dest.ref.second >> LabelIO{ ":)" };
  }

  std::istream& operator>>(std::istream& in, StringIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    return in >> std::quoted(dest.ref);
  }

  std::istream& operator>>(std::istream& in, ExpectedCharIO&& exp) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    char c = in.get();
    bool isExpected = exp.ignoreCase ? (tolower(c) == tolower(exp.val)) : (c == exp.val);
    if (in && !isExpected) {
      in.setstate(std::ios::failbit);
    }
    return in;
  }

  std::istream& operator>>(std::istream& in, LabelIO&& exp) {
    std::istream::sentry sentry(in);
    if (!sentry) {
      return in;
    }
    iofmtguard fmtguard(in);
    in >> std::noskipws;
    for (const char& c : exp.val) {
      in >> ExpectedCharIO{ c, exp.ignoreCase };
    }
    return in;
  }
}
