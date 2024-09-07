#ifndef STREAM_GUARD_H
#define STREAM_GUARD_H

#include <iostream>

class StreamGuard {
public:
  StreamGuard(std::ios& stream);
  ~StreamGuard();
private:
  std::ios& stream_;
  std::ios::fmtflags state_;
  std::streamsize precision_;
  char fill_;
};
#endif
