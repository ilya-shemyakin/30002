// DataStruct.h
#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include <string>
#include <iostream>

namespace yurev
{
    struct DataStruct
    {
        double key1;
        unsigned long long key2;
        std::string key3;
    };

    bool operator<(DataStruct &rhs, DataStruct &lhs);
    std::istream &operator>>(std::istream &in, DataStruct &dest);
    std::ostream &operator<<(std::ostream &out, const DataStruct &dest);
}

#endif // DATASTRUCT_H_
