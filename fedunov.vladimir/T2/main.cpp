#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataStructVector;
  DataStruct ds;

  std::istream_iterator<DataStruct> in_iter(std::cin), eof;
  std::copy(in_iter, eof, std::back_inserter(dataStructVector));

  std::sort(dataStructVector.begin(), dataStructVector.end());

  std::ostream_iterator<DataStruct> out_iter(std::cout, "\n");
  std::copy(dataStructVector.begin(), dataStructVector.end(), out_iter);

  return 0;
}
