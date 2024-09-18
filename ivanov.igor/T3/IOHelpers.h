#pragma once
// IOHelpers.h
#ifndef IOHELPERS_H_
#define IOHELPERS_H_

#include <iostream>

namespace ivanov
{
    class StreamGuard
    {
    public:
        StreamGuard(std::basic_ios<char>& s);
        ~StreamGuard();

    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios<char>::fmtflags fmt_;
    };

    struct ExpectedCharIO
    {
        const char& val;
        bool ignoreCase = false;
    };

    std::istream& operator>>(std::istream& in, const ExpectedCharIO&& exp);
}

#endif // IOHELPERS_H_
