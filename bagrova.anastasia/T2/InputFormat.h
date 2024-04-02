#pragma once

#ifndef INPUT_FORMAT_H
#define INPUT_FORMAT_H

namespace IO
{
    struct DelimiterIO
    {
        char exp;
    };

    struct LabelIO
    {
        std::string str;
    };

    struct ChrLitIO
    {
        char c;
    };

    // num/den
    struct RatLspIO
    {
        long long num;
        unsigned long long den;
    };

    struct StrIO
    {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, StrIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, ChrLitIO& data);
    std::istream& operator>>(std::istream& in, RatLspIO& data);
}
#endif
