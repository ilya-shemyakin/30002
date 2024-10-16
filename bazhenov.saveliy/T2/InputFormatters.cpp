#include "InputFormatters.h"

#include <sstream>
#include <iomanip>
#include <execution>

#include "StreamGuard.h"

std::istream& operator>>(std::istream& in, DelimiterI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    in >> c;
    if (in && (std::tolower(c) != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, StringI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    return std::getline(in >> DelimiterI{ '"' }, dest.ref, '"');
}

std::istream& operator>>(std::istream& in, LongLongI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    StreamGuard guard(in);
    return in >> dest.ref >> LabelI{ "ull", true };
}

std::istream& operator>>(std::istream& in, OctalLongLongI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    StreamGuard guard(in);
    in >> DelimiterI{ '0' };
    return in >> std::oct >> dest.ref;
}

std::istream& operator>>(std::istream& in, ExpectedCharI&& exp)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = in.get();
    bool isExpected = exp.ignoreCase ? (tolower(c) == tolower(exp.val)) : (c == exp.val);
    if (in && !isExpected) {
        in.setstate(std::ios::failbit);
    }
    return in;
}

std::istream& operator>>(std::istream& in, LabelI&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    StreamGuard guard(in);
    in >> std::noskipws;
    for (const char& c : dest.ref) {
        in >> ExpectedCharI{ c, dest.ignoreCase };
    }
    return in;
}
