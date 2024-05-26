#include <iostream>
#include <vector>
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

    return 0;
}
