#include "DataStruct.h"
#include <iostream>
#include <limits.h>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace ivatshenko;
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

/*
(:key1 5.22E-2:key2 3123124412LL:key3 brakovanniyNO:)
(:key1 3.22E-2:key3 "idi nahuyOK":key2 3124412LL:)
(:key1 0.22E-2:key2 3123124412LL:key3 "idi nahuyOK":)
(:key1 5.22E-2:key2 31231442L:key3 "idi nahuyNO":)
(:key1 5.22E-2:key2 3123124412LL:key3 "idi huyOK":)
(:key2 3123124412LL:key1 5.22E-2:key3 "idi nahuyOK":)
(:key1 1.22E-2:key2 31124412LL:key3 "idi nhuyOK":)
*/