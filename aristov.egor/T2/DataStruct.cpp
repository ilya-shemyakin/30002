#include "DataStruct.h"
#include "StreamGuard.h"
#include "InputFormat.h"
#include <iomanip>

bool operator<(const DataStruct& left, const DataStruct& right) {
  if (left.key1 != right.key1) {
    return left.key1 < right.key1;
  }
  else if (abs(left.key2) != abs(right.key2)) {
    return abs(left.key2) < abs(right.key2);
  }
  else {
    return left.key3.length() < right.key3.length();
  }
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct) {
  std::ostream::sentry sentry(out);
  if (!sentry) {
    return out;
  }
  StreamGuard guard(out);
  out << "(:key1 0x" << std::uppercase << std::hex << dataStruct.key1;
  out << ":key2 #c(" << std::fixed << std::setprecision(1) << dataStruct.key2.real() << " " << dataStruct.key2.imag() << ")";
  out << ":key3 \"" << dataStruct.key3 << "\":)";
  return out;
}

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  std::istream::sentry sentry(in);
  if (!sentry) {
    return in;
  }
  DataStruct input;
  {
    using sep = DelimiterIO;
    using label = LabelIO;
    using str = StringIO;
    using num = LongLongIO;
    using cmp = CmpLspIO;
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++) {
      std::string key;
      in >> sep{ ':' } >> label{ key };
      if (key == "key1") {
        in >> num{ input.key1 };
      }
      else if (key == "key2") {
        in >> cmp{ input.key2 };
      }
      else if (key == "key3") {
        in >> str{ input.key3 };
      }
      else {
        in.setstate(std::ios::failbit);
      }
    }
    in >> sep{ ':' } >> sep{ ')' };
  }
  if (in.fail()) {
    in.setstate(std::ios::failbit);
  }
  dataStruct = input;
  return in;
}
