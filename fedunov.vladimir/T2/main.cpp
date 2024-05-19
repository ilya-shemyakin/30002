#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataStructVector;
  DataStruct ds;

  while (std::cin >> ds)
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    else
    {
      dataStructVector.push_back(ds);
    }
  }

  std::sort(dataStructVector.begin(), dataStructVector.end());

  std::copy(dataStructVector.begin(), dataStructVector.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n"));

  return 0;
}
