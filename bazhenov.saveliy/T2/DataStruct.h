#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#include <iostream>

struct DataStruct {
    unsigned long long key1 = 0;
    unsigned long long key2 = 0;
    std::string key3;

    DataStruct& operator=(const DataStruct& other) = default;
};

bool operator<(const DataStruct& rhs, const DataStruct& lhs);

std::istream& operator>>(std::istream& in, DataStruct& dest);
std::ostream& operator<<(std::ostream& out, const DataStruct& dest);

#endif
    