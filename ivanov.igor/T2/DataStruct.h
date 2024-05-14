#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <iostream>
#include <sstream>
#include <iomanip>
#include "IO.h"
namespace data
{
    struct DataStruct
    {
        std::string key1;
        long long key2;
        std::string key3;
    };
    bool operator<(DataStruct& right, DataStruct& left);
    std::istream& operator>>(std::istream& in, DataStruct& ds);
    std::ostream& operator<<(std::ostream& out, const DataStruct& ds);
}
#endif