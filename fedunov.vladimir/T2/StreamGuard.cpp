#include "StreamGuard.h"
#include <iostream>

namespace fedunov
{
  StreamGuard::StreamGuard(std::basic_ios<char>& s) : s_(s),
    fill_(s.fill()),
    precision_(s.precision()),
    fmt_(s.flags())
  {}
  StreamGuard::~StreamGuard()
  {
    s_.fill(fill_);
    s_.precision(precision_);
    s_.flags(fmt_);
  }
}
