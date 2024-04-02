#pragma once

#ifndef STREAM_GUARD_H
#define STREAM_GUARD_H

#include <iostream>

class StreamGuard
{
public:
    StreamGuard(std::istream& in) :
        stream(in),
        precision(in.precision()),
        flags(in.flags())
    {}
    ~StreamGuard()
    {
        stream.precision(precision);
        stream.flags(flags);
    }

private:
    std::istream& stream;
    std::streamsize precision;
    std::basic_ios<char>::fmtflags flags;
};
#endif
