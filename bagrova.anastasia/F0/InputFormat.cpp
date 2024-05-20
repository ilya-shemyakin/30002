#include <iostream>

#include "InputFormat.h"
#include "StreamGuard.h"

std::istream& operator>>(std::istream& in, DelimiterIO&& dest) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }
    char c = '0';
    c = in.peek();
    if (in && (c != dest.exp)) {
        in.setstate(std::ios::failbit);
    }
    else {
        in.get();
    }
    return in;
}

std::istream& operator>>(std::istream& in, Edge& edge) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    StreamGuard guard(in);
    in >> std::noskipws;

    int vFirst, vSecond, weight;
    in >> vFirst;
    in >> DelimiterIO{ ' ' };
    if (!in) {
        return in;
    }
    in >> vSecond;

    in >> DelimiterIO{ ' ' };
    if (!in) {
        return in;
    }
    in >> weight;

    if (!in) {
        return in;
    }

    edge = { vFirst, vSecond, weight };
    return in;
}
