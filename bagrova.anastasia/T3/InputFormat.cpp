#include <iostream>
#include <fstream>

#include <algorithm>
#include <iterator>
#include <limits>

#include "InputFormat.h"
#include "Polygon.h"
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

std::istream& operator>>(std::istream& in, Point& point) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    int x, y;
    in >> DelimiterIO{ ' ' } >> DelimiterIO{ '(' };
    if (!in) {
        return in;
    }

    in >> x >> DelimiterIO{ ';' } >> y >> DelimiterIO{ ')' };

    if (!in) {
        return in;
    }

    point = { x, y };
    return in;
}

std::istream& operator>>(std::istream& in, Polygon& poly) {
    std::istream::sentry sentry(in);
    if (!sentry) {
        return in;
    }

    StreamGuard guard(in);
    in >> std::noskipws;

    Polygon tmpPoly;
    const int MIN_COUNT_SIDE = 3;
    int n;
    in >> n;

    if (n < MIN_COUNT_SIDE) {
        in.setstate(std::ios::failbit);
        return in;
    }

    std::copy_n(
        std::istream_iterator<Point>(in),
        n,
        std::back_inserter(tmpPoly.points)
    );

    if (!in) {
        return in;
    }

    poly = tmpPoly;
    return in;
}

void load(std::string fileName, std::vector<Polygon>& data) {
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Not such file!\n");
    }

    while (!file.eof()) {
        std::copy(
            std::istream_iterator<Polygon>(file),
            std::istream_iterator<Polygon>(),
            back_inserter(data)
        );

        if (file.fail()) {
            bool eofFlag = file.eof();
            file.clear();
            if (eofFlag) {
                file.setstate(std::ios::eofbit);
            }
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    file.close();
}
