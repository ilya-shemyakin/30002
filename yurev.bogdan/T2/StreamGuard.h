// StreamGuard.h
#ifndef STREAMGUARD_H_
#define STREAMGUARD_H_

#include <iostream>

namespace yurev
{
    class StreamGuard
    {
    public:
        StreamGuard(std::basic_ios<char> &s);
        ~StreamGuard();

    private:
        std::basic_ios<char> &s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };
}

#endif // STREAMGUARD_H_
