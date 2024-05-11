#ifndef INPUT_FORMATS_H
#define INPUT_FORMATS_H

#include <string>
#include <complex>

namespace nspaceg
{
    // {char}
    struct DelimiterIO
    {
        char exp;
    };

    // key{1|2|3}
    struct LabelIO
    {
        std::string exp;
    };

    // {long long}ll || {long long}LL
    struct SllLitIO
    {
        long long& ref;
    };

    // #c({double} {double})
    struct CmpLspIO
    {
        std::complex<double>& ref;
    };

    // "{string}"
    struct StringIO
    {
        std::string& ref;
    };

    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);
    std::istream& operator>>(std::istream& in, SllLitIO&& dest);
    std::istream& operator>>(std::istream& in, CmpLspIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
}

#endif
