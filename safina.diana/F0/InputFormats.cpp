#include "InputFormats.h"

namespace formatsIO
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.unget();
            in.setstate(std::ios::failbit);
        }
        return in;
    }
}