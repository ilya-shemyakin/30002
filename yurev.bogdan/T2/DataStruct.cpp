#include <iomanip>
#include <istream>
#include <set>

#include "DataStruct.h"
#include "InputAdapters.h"
#include "StreamGuard.h"

namespace yurev
{
    bool operator<(DataStruct &lhs, DataStruct &rhs)
    {
        if (lhs.key1 != rhs.key1)
        {
            return lhs.key1 < rhs.key1;
        }
        if (lhs.key2 != rhs.key2)
        {
            return lhs.key2 < rhs.key2;
        }
        return lhs.key3.length() < rhs.key3.length();
    }

    std::istream &operator>>(std::istream &in, DataStruct &dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input{0, 0, ""};
        {
            StreamGuard guard(in);
            using ull = UnsignedLongLongIO;
            using dbl = DoubleIO;
            using str = StringIO;
            using chr = ExpectedCharIO;
            using label = LabelIO;
            constexpr std::size_t FIELDS_COUNT = 3;
            int keyId = 0;
            in >> chr{'('};
            for (size_t i = 0; i < FIELDS_COUNT; i++)
            {
                in >> label{":key"} >> keyId;
                if (keyId == 1)
                {
                    in >> dbl{input.key1};
                }
                else if (keyId == 2)
                {

                    in >> ull{input.key2};
                }
                else if (keyId == 3)
                {
                    in >> str{input.key3};
                }
                else
                {
                    in.setstate(std::istream::failbit);
                    continue;
                }
            }
            in >> label{":)"};
        }
        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream &operator<<(std::ostream &out, const DataStruct &src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }
        StreamGuard guard(out);
        out << "(:";
        out << "key1 " << std::fixed << std::setprecision(1) << src.key1 << "d:";
        out << "key2 " << src.key2 << "ull" << ":";
        out << "key3 " << std::quoted(src.key3) << ":";
        out << ")";
        return out;
    }
}
