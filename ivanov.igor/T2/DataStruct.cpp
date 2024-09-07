#include "DataStruct.h"

namespace check
{
    bool operator<(const DataStruct& left, const DataStruct& right)
    {
        if (left.key1 != right.key1)
        {
            return left.key1 < right.key1;
        }
        if (left.key2 != right.key2)
        {
            return left.key2 < right.key2;
        }
        return left.key3.length() < right.key3.length();
    }

    std::istream& operator>>(std::istream& in, DataStruct& ds)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct data{ "", 0, "" };
        {
            StreamGuard guard(in);
            const std::size_t COUNT_OF_FIELDS = 3;
            char keyId = '0';
            in >> std::noskipws;
            in >> DelimiterIO{ '(' };
            for (std::size_t i = 0; i < COUNT_OF_FIELDS; i++)
            {
                in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
                in >> keyId;
                in >> DelimiterIO{ ' ' };
                if (keyId == '1')
                {
                    in >> LitDoubleIO{ data.key1 };
                    continue;
                }
                if (keyId == '2')
                {
                    in >> LongLongIO{ data.key2 };
                    continue;
                }
                if (keyId == '3')
                {
                    in >> StringIO{ data.key3 };
                    continue;
                }
                if (keyId != '1' && keyId != '2' && keyId != '3')
                {
                    in.setstate(std::istream::failbit);
                    break;
                }
            }
            in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
            if (in)
            {
                ds = data;
            }
            return in;
        }
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        out << "(";
        out << ":key1 " << ds.key1;
        out << ":key2 " << ds.key2 << "ll";
        out << ":key3 " << std::quoted(ds.key3) << ":";
        out << ")";
        return out;
    }
}

