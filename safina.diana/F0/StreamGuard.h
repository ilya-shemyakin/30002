#ifndef STREAM_GUARD_H
#define STREAM_GUARD_H

#include <iostream>

namespace formatsIO
{
    // Scope guard для возврата потока в первоначальное состояние
    class StreamGuard
    {
    public:
        StreamGuard(std::basic_ios< char >& s);
        ~StreamGuard();
    private:
        std::basic_ios< char >& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };
}

#endif
