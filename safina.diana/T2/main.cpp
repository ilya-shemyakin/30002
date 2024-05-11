#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
#include <algorithm>
#include <tuple>

#include "DataStruct.h"

int main()
{
    using nspace::DataStruct;
    std::vector<DataStruct> data;

    while (!std::cin.eof())
    {
        std::copy(
            std::istream_iterator<DataStruct>(std::cin),
            std::istream_iterator<DataStruct>(),
            std::back_inserter(data)
        );

        if (std::cin.fail())
        {
            bool eof = std::cin.eof();
            std::cin.clear();
            if (eof)
            {
                std::cin.setstate(std::ios::eofbit);
            }
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }

    auto comparator = [](const DataStruct& a, const DataStruct& b)
    {
        return std::make_tuple(a.key1, abs(a.key2), a.key3.size()) <
            std::make_tuple(b.key1, abs(b.key2), b.key3.size());
    };

    std::sort(data.begin(), data.end(), comparator);

    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator<DataStruct>(std::cout, "\n")
    );

    return 0;
}
