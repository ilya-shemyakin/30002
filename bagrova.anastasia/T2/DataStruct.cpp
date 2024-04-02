#include <iostream>
#include <sstream>

#include "DataStruct.h"
#include "InputFormat.h"
#include "StreamGuard.h"

namespace IO
{
    bool operator==(const DataStruct& s1, const DataStruct& s2)
    {
        return s1.key1 == s2.key1 && s1.key2 == s2.key2 && s1.key3 == s2.key3;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& data)
    {
        out << "(:key1 '" << data.key1 << '\'' <<
            ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)" <<
            ":key3 \"" << data.key3 << "\":)";
        return out;
    }

    std::istream& readData(std::istream& in, DataStruct& rec)
    {
        StreamGuard guard(in);
        ChrLitIO symbol;
        RatLspIO rat;
        std::string str;

        in >> std::noskipws;
        in >> DelimiterIO{ '(' };

        for (int i = 0; i < 3; i++)
        {
            in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
            char keyNumber = in.get();
            in >> DelimiterIO{ ' ' };

            if (keyNumber == '1')
            {
                in >> symbol;
            }
            else if (keyNumber == '2')
            {
                in >> rat;
            }
            else if (keyNumber == '3')
            {
                in >> StrIO{ str };
            }
            else
            {
                in.setstate(std::ios::failbit);
                return in;
            }
        }

        in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        if (in)
        {
            rec.key1 = symbol.c;
            rec.key2 = { rat.num, rat.den };
            rec.key3 = str;
        }
        return in;
    }

    std::istream& operator>>(std::istream& stream, DataStruct& rec)
    {
        std::istream::sentry sentry(stream);
        if (!sentry)
        {
            return stream;
        }

        std::string line;
        while (getline(stream, line, '\n'))
        {
            std::istringstream in(line);
            DataStruct tempRec;
            if (readData(in, tempRec))
            {
                std::string tail;
                if (!getline(in, tail) || tail.empty())
                {
                    rec = tempRec;
                    break;
                }
            }
        }
        return stream;
    }
}
