#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <tuple>

#include "DataStruct.h"

int main()
{
    using IO::DataStruct;

    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> begCin(std::cin);

    std::copy(
        std::istream_iterator< DataStruct >(begCin),
        std::istream_iterator< DataStruct >(),
        back_inserter(data)
    );

    auto Comparator = [](const DataStruct& s1, const DataStruct& s2)
    {
        double rat1 = static_cast<double>(s1.key2.first) / s1.key2.second;
        double rat2 = static_cast<double>(s2.key2.first) / s2.key2.second;
        auto left = std::make_tuple(s1.key1, rat1, s1.key3.size());
        auto right = std::make_tuple(s2.key1, rat2, s2.key3.size());
        return left < right;
    };

    std::sort(data.begin(), data.end(), Comparator);

    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );

    return 0;
}
