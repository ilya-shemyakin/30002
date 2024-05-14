#ifndef IO_H
#define IO_H
#include <istream>
#include <string>
#include <iomanip>
#include "DataStruct.h"
#include <regex>

namespace DataCheck
{
    struct LitDoubleIO
    {
        std::string& value;
    };

    struct LongLongIO
    {
        long long& value;
    };

    struct StringIO
    {
        std::string& ref;
    };

    struct DelimiterIO
    {
        char exp;
    };

    struct LabelIO
    {
        const std::string& exp;
    };

    bool isValidLiteral(const std::string& str);

    class StreamGuard
    {
    public:
        StreamGuard(std::basic_ios<char>& s);
        ~StreamGuard();
    private:
        std::basic_ios<char>& s_;
        char fill_;
        std::streamsize precision_;
        std::basic_ios< char >::fmtflags fmt_;
    };

    std::istream& operator>>(std::istream& in, LitDoubleIO&& dest);
    std::istream& operator>>(std::istream& in, LongLongIO&& dest);
    std::istream& operator>>(std::istream& in, StringIO&& dest);
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
    std::istream& operator>>(std::istream& in, LabelIO&& dest);

}
#endif
