#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H

#include <utility>
#include <string>

namespace IO
{
    struct DataStruct
    {
        char key1;
        std::pair<long long, unsigned long long> key2;
        std::string key3;
    };
    std::ostream& operator<<(std::ostream& out, const DataStruct& data);
    std::istream& operator>>(std::istream& stream, DataStruct& rec);
}
#endif
