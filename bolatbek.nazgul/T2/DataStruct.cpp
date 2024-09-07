#include <iostream>
#include <vector>
<<<<<<< HEAD
#include <algorithm>
#include <iterator>
#include <sstream>

struct DataStruct
{
    unsigned long long key1;
    char key2;
    std::string key3;
};

bool operator<(const DataStruct& lhs, const DataStruct& rhs)
{
    if (lhs.key1 != rhs.key1)
        return lhs.key1 < rhs.key1;
    if (lhs.key2 != rhs.key2)
        return lhs.key2 < rhs.key2;
    return lhs.key3.size() < rhs.key3.size();
}

int main()
{
    std::vector<DataStruct> dataVector;

    std::string line;
    while (std::getline(std::cin, line))
    {
        std::istringstream iss(line);
        DataStruct data;
        char dummy;

        if (iss >> dummy >> dummy >> dummy >> dummy >> data.key1 >> dummy >> data.key2 >> dummy >> dummy >> data.key3 >> dummy)
        {
            dataVector.push_back(data);
        }
    }

    std::sort(dataVector.begin(), dataVector.end());

    std::copy(dataVector.begin(), dataVector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));

    return 0;
}

#include <iostream>
#include <sstream>
#include "datastruc.h"

struct DataStruct {
    int key1;
    std::string key2;

    DataStruct(int k1, const std::string& k2) : key1(k1), key2(k2) {}
};

DataStruct parseDataStruct(const std::string& data) {
    int key1;
    std::string key2;

    std::istringstream iss(data);
    iss >> key1 >> key2;

    return DataStruct(key1, key2);
}

int main() {
    std::string inputData = "42 Hello";
    DataStruct myData = parseDataStruct(inputData);

    std::cout << "Parsed Data:\n";
    std::cout << "Key 1: " << myData.key1 << "\n";
    std::cout << "Key 2: " << myData.key2 << "\n";
=======
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
>>>>>>> 196f8d73eb5b165c92e997b793b0549efeb97ca6

    return 0;
}
