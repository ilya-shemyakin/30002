#include "DataStruct.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace data;
int main()
{
    std::vector<DataStruct> vec;
    while (!std::cin.eof())
    {
        std::copy(
            std::istream_iterator< DataStruct >(std::cin),
            std::istream_iterator< DataStruct >(),
            back_inserter(vec)
        );
        if (std::cin.fail() && !std::cin.eof())
        {
            std::cin.clear();
        }
    }
    std::sort(vec.begin(), vec.end());

    std::copy(
        std::begin(vec),
        std::end(vec),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
    return 0;
}