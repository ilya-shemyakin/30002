#include <iostream>
#include <iomanip>
#include <string>

#include "InputFormat.h"

namespace IO
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        c = in.get();
        if (in && (c != dest.exp))
        {
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    // "string"
    std::istream& operator>>(std::istream& in, StrIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
    }

    //key
    std::istream& operator>>(std::istream& in, LabelIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        char c = '0';
        for (size_t i = 0; i < dest.str.size(); i++)
        {
            c = in.get();
            if (in && (c != dest.str[i]))
            {
                in.setstate(std::ios::failbit);
                break;
            }
        }
        return in;
    }

    // 'c'
    std::istream& operator>>(std::istream& in, ChrLitIO& data)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '\'' } >> data.c >> DelimiterIO{ '\'' };
    }

    // (:N -1:D 5:)
    std::istream& operator>>(std::istream& in, RatLspIO& data)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }

        in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >>
            DelimiterIO{ 'N' } >> DelimiterIO{ ' ' };
        if (!in)
        {
            return in;
        }

        long long tempNum = 0;
        in >> tempNum;
        if (!in)
        {
            return in;
        }
        in >> DelimiterIO{ ':' } >> DelimiterIO{ 'D' } >> DelimiterIO{ ' ' };

        std::string temp;
        getline(in, temp, ':');
        if (temp.size() == 0 || !isdigit(temp[0]))
        {
            in.setstate(std::ios::failbit);
            return in;
        }

        int i = 0;
        while (temp[i])
        {
            if (!isdigit(temp[i]))
            {
                in.setstate(std::ios::failbit);
                return in;
            }
            i += 1;
        }
        unsigned long long tempDen = 0;
        tempDen = stoll(temp);

        in >> DelimiterIO{ ')' };
        if (in)
        {
            data.num = tempNum;
            data.den = tempDen;
        }
        return in;
    }
}
