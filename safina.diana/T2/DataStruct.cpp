#include "DataStruct.h"
#include "InputFormats.h"
#include "StreamGuard.h"

#include <iomanip>

namespace nspace
{
    std::istream& operator>>(std::istream& in, DataStruct& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        DataStruct input;

        StreamGuard guard(in);

        {
            in >> std::noskipws;
            in >> DelimiterIO{ '(' };

            const int KEY_NUMBER = 3;
            for (int i = 1; i <= KEY_NUMBER; ++i)
            {
                in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
                char keyNumber = in.get();
                in >> DelimiterIO{ ' ' };

                switch (keyNumber)
                {
                    case '1':
                        in >> SllLitIO{ input.key1 };
                        break;
                    case '2':
                        in >> CmpLspIO{ input.key2 };
                        break;
                    case '3':
                        in >> StringIO{ input.key3 };
                        break;
                    default:
                        in.setstate(std::ios::failbit);
                        return in;
                }
            }
            in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
        }

        if (in)
        {
            dest = input;
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DataStruct& src)
    {
        std::ostream::sentry sentry(out);
        if (!sentry)
        {
            return out;
        }

        StreamGuard guard(out);

        out << "(:";
        out << "key1 " << src.key1 << "ll" << ':';
        out << "key2 " << "#c(" << std::fixed << std::setprecision(1) << src.key2.real() << ' ' << src.key2.imag() << "):";
        out << "key3 \"" << src.key3 << "\":)";
        return out;
    }
}
