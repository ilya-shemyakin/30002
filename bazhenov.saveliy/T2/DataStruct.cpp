#include <sstream>
#include <iomanip>
#include <execution>

#include "DataStruct.h"
#include "InputFormatters.h"
#include "StreamGuard.h"

bool operator<(const DataStruct& lhs, const DataStruct& rhs) {
    if (lhs.key1 != rhs.key1) {
        return lhs.key1 < rhs.key1;
    }
    if (lhs.key2 != rhs.key2) {
        return lhs.key2 < rhs.key2;
    }
    return lhs.key3.size() < rhs.key3.size();
}

std::istream& operator>>(std::istream& in, DataStruct& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    DataStruct input;
    using sep = DelimiterI;
    using label = LabelI;
    using str = StringI;
    using OctNum = OctalLongLongI;
    using num = LongLongI;

    int keyId = 0;
    in >> sep{ '(' };
    for (size_t i = 0; i < 3; i++) {
        std::string key;

        in >> label{ ":key" } >> keyId;

        if (keyId == 1) {
            in >> num{ input.key1 };
        }
        else if (keyId == 2) {
            in >> OctNum{ input.key2 };
        }
        else if (keyId == 3) {
            in >> str{ input.key3 };
        }
        else {
            in.setstate(std::ios::failbit);
            continue;
        }
    }
        in >> label{ ":)" };

        if (!in) {
            in.setstate(std::ios::failbit);
        }
        dest = input;
        return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dest) {
    std::ostream::sentry sentry(out);
    if (!sentry) {
        return out;
    }
    StreamGuard guard(out);
    out << "(:";
    out << "key1 " << std::fixed << std::setprecision(1) << dest.key1 << "ull:";
    out << "key2 0" << std::oct << std::uppercase << dest.key2 << ":";
    out << "key3 \"" << dest.key3 << "\"";
    out << ":)";
    return out;
}
