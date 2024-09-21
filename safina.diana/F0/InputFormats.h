#ifndef INPUT_FORMATS_H
#define INPUT_FORMATS_H

#include <iostream>

namespace formatsIO
{
    struct DelimiterIO
    {
        char exp;
    };
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
}

#endif
