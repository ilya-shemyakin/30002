#include <iostream>

#include "InputFormats.h"

namespace nspace
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
        if (in && (std::tolower(c) != dest.exp))
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
        char c = '0';
        for (auto i = dest.exp.begin(); i != dest.exp.end(); ++i)
        {
            in >> c;
            if (in && (c != *i))
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, SllLitIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
       return in >> dest.ref >> DelimiterIO{ 'l' } >> DelimiterIO{ 'l' };
    }

    std::istream& operator>>(std::istream& in, CmpLspIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        int realIntegral = 0;
        int realFractional = 0;
        int imagIntegral = 0;
        int imagFractional = 0;

        in >> DelimiterIO{ '#' } >> DelimiterIO{ 'c' } >> DelimiterIO{ '(' } >>
                realIntegral >> DelimiterIO{ '.' } >> realFractional >> DelimiterIO{ ' ' } >>
                imagIntegral >> DelimiterIO{ '.' } >> imagFractional >> DelimiterIO{ ')' };

        dest.ref.real(static_cast< double >(realIntegral) + static_cast< double >(realFractional) / 10.0);
        dest.ref.imag(static_cast< double >(imagIntegral) + static_cast< double >(imagFractional) / 10.0);
        return in;
    }

    std::istream& operator>>(std::istream& in, StringIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }
}
