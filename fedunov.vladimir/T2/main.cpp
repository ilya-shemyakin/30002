#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataStructVector;

  std::istream_iterator<DataStruct> in_begin(std::cin), in_end;
  std::copy_if(in_begin, in_end, std::back_inserter(dataStructVector),
    [](const DataStruct& ds) { return !std::cin.fail(); });

  std::sort(dataStructVector.begin(), dataStructVector.end());

  std::ostream_iterator<DataStruct> out_begin(std::cout, "\n");
  std::copy(dataStructVector.begin(), dataStructVector.end(), out_begin);

  return 0;
}
