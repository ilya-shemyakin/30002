#include "InputFormatters.h"
#include "Polygon.h"
#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <limits>

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

void load(const std::string& fileName, std::vector<Polygon>& data) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Not such file!\n");
    }

    while (!file.eof()) {
        std::copy(
            std::istream_iterator<Polygon>(file),
            std::istream_iterator<Polygon>(),
            std::back_inserter(data)
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
