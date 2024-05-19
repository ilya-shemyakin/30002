#include "DataStruct.h"


namespace ivatshenko
{
    bool operator<(DataStruct& left, DataStruct& right)
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
        DataStruct data{ 0, 0, "" };
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
                    in >> SciDoubleIO{ data.key1 };
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

    std::string myScientific(double x)
    {
        std::stringstream ss;
        ss << std::scientific << x;
        std::string str = ss.str();
        size_t i = str.find('e');
        while (str[i - 1] == '0' && str[i - 2] != '.')
        {
            str.erase(i - 1, 1);
            i = str.find('e');
        }
        while (str[i + 2] == '0')
        {
            str.erase(i + 2, 1);
            i = str.find('e');
        }
        return str;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        StreamGuard guard(out);
        out << "(";
        out << ":key1 " << myScientific(ds.key1);
        out << ":key2 " << ds.key2 << "ll";
        out << ":key3 " << std::quoted(ds.key3) << ":";
        out << ")";
        return out;
    }
}
