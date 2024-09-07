#include <iomanip>

#include "InputAdapters.h"
#include "StreamGuard.h"

namespace yurev
{
    std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        StreamGuard guard(in);
        return in >> dest.ref >> LabelIO{"ull", true};
    }

    std::istream &operator>>(std::istream &in, DoubleIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        StreamGuard guard(in);
        return in >> dest.ref >> LabelIO{"d", true};
    }

    std::istream &operator>>(std::istream &in, StringIO &&dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> std::quoted(dest.ref);
    }

    std::istream &operator>>(std::istream &in, ExpectedCharIO &&exp)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = in.get();
        bool isExpected = exp.ignoreCase ? (tolower(c) == tolower(exp.val)) : (c == exp.val);
        if (in && !isExpected)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream &operator>>(std::istream &in, LabelIO &&exp)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        StreamGuard guard(in);
        in >> std::noskipws;
        for (const char &c : exp.val)
        {
            in >> ExpectedCharIO{c, exp.ignoreCase};
        }
        return in;
    }
}
