#include "IO.h"
namespace ivatshenko
{
    StreamGuard::StreamGuard(std::basic_ios<char>& s) :
        s_(s),
        fill_(s.fill()),
        precision_(s.precision()),
        fmt_(s.flags())
    {}

    StreamGuard::~StreamGuard()
    {
        s_.fill(fill_);
        s_.precision(precision_);
        s_.flags(fmt_);
    }

    bool isDoubleSCI(const std::string& str)
    {
        std::regex pattern("^[-+]?[0-9]*\\.?[0-9]+([eE][-+]?[0-9]+)$");
        return std::regex_match(str, pattern);
    }

    std::istream& operator>>(std::istream& in, SciDoubleIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        std::string str;
        std::getline(in, str, ':'); 
        in.putback(':');
        if (isDoubleSCI(str))
        {
            std::stringstream ss(str);
            ss >> dest.value; 
        }
        else
        {
            in.setstate(std::ios::failbit); 
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LongLongIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> dest.value >> LabelIO{ "ll" };
        if (!in)
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        in >> std::quoted(dest.ref);
        return in;
    }

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
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        StreamGuard guard(in);
        in >> std::noskipws;
        char c = '0';
        for (size_t i = 0; i < dest.exp.size(); i++)
        {
            in >> c;
            if (in && (c != dest.exp[i]))
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }
        return in;
    }
}
