#ifndef INPUT_FORMATS_H
#define INPUT_FORMATS_H

#include "Polygon.h"

namespace shapes
{
    struct DelimiterIO
    {
        char exp;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, Point& dest);
    std::istream& operator>>(std::istream& in, Polygon& dest);

    const int MIN_VERTEXES_NUMBER = 3;
}

#endif
