#include <iostream>
#include <sstream>

#include "DataStruct.h"
#include "InputFormat.h"
#include "StreamGuard.h"

namespace IO
{
    std::ostream& operator<<(std::ostream& out, const DataStruct& data)
    {
        out << "(:key1 '" << data.key1 << '\'' <<
            ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)" <<
            ":key3 \"" << data.key3 << "\":)";
        return out;
    }

    std::istream& operator>>(std::istream& stream, DataStruct& rec)
    {
        std::istream::sentry sentry(stream);
        if (!sentry)
        {
            stream.setstate(std::ios::failbit);
            return stream;
        }

        StreamGuard guard(stream);
        ChrLitIO symbol;
        RatLspIO rat;
        std::string str;
        const int COUNT_KEY = 3;

        stream >> std::noskipws;
        stream >> DelimiterIO{ '(' };

        for (int i = 0; i < COUNT_KEY; i++)
        {
            stream >> DelimiterIO{ ':' } >> LabelIO{ "key" };
            char keyNumber = stream.get();
            stream >> DelimiterIO{ ' ' };

            if (keyNumber == '1')
            {
                stream >> symbol;
            }
            else if (keyNumber == '2')
            {
                stream >> rat;
            }
            else if (keyNumber == '3')
            {
                stream >> StrIO{ str };
            }
            else
            {
                stream.setstate(std::ios::failbit);
                return stream;
            }
        }

        stream >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        if (stream)
        {
            rec.key1 = symbol.c;
            rec.key2 = { rat.num, rat.den };
            rec.key3 = str;
        }
        return stream;
    }
}
