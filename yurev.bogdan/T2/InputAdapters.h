// InputAdapters.h
#ifndef INPUTADAPTERS_H_
#define INPUTADAPTERS_H_

#include <istream>
#include <string>

namespace yurev
{
    struct DoubleIO
    {
        double &ref;
    };

    struct UnsignedLongLongIO
    {
        unsigned long long &ref;
    };

    struct StringIO
    {
        std::string &ref;
    };

    struct ExpectedCharIO
    {
        const char &val;
        bool ignoreCase = false;
    };

    struct LabelIO
    {
        const std::string &val;
        bool ignoreCase = false;
    };

    std::istream &operator>>(std::istream &in, DoubleIO &&dest);
    std::istream &operator>>(std::istream &in, UnsignedLongLongIO &&dest);
    std::istream &operator>>(std::istream &in, StringIO &&dest);
    std::istream &operator>>(std::istream &in, ExpectedCharIO &&exp);
    std::istream &operator>>(std::istream &in, LabelIO &&exp);
}

#endif // INPUTADAPTERS_H_
