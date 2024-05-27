#include <iostream>
#include <vector>
#include <string>
#include <complex>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <regex>

struct DataStruct {
    unsigned long long key1;  // ULL OCT
    std::complex<double> key2;  // CMP LSP
    std::string key3;
};

unsigned long long octal_to_ull(const std::string& str) {
    return std::stoull(str, nullptr, 8);
}

std::istream& operator>>(std::istream& is, DataStruct& data) {
    std::string line;
    if (std::getline(is, line)) {
        std::regex re(R"(\(:key1 ([0-7]+):key2 #c\(([^ ]+) ([^ ]+)\):key3 "([^"]+)":\))");
        std::smatch match;
        if (std::regex_match(line, match, re)) {
            data.key1 = octal_to_ull(match[1].str());
            double real = std::stod(match[2].str());
            double imag = std::stod(match[3].str());
            data.key2 = std::complex<double>(real, imag);
            data.key3 = match[4].str();
        } else {
            is.setstate(std::ios::failbit);
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const DataStruct& data) {
    os << "(:key1 " << std::oct << data.key1
       << ":key2 #c(" << data.key2.real() << " " << data.key2.imag()
       << "):key3 \"" << data.key3 << "\":)";
    return os;
}

int main() {
    std::vector<DataStruct> dataStructs;

    std::copy(std::istream_iterator<DataStruct>(std::cin),
              std::istream_iterator<DataStruct>(),
              std::back_inserter(dataStructs));

    std::sort(dataStructs.begin(), dataStructs.end(), [](const DataStruct& a, const DataStruct& b) {
        if (a.key1 != b.key1)
            return a.key1 < b.key1;
        if (std::abs(a.key2) != std::abs(b.key2))
            return std::abs(a.key2) < std::abs(b.key2);
        return a.key3.size() < b.key3.size();
    });

    std::copy(dataStructs.begin(), dataStructs.end(),
              std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}
