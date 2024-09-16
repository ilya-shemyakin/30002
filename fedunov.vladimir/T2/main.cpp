#include <iostream>
#include <iomanip>
#include <iterator>
#include <vector>
#include <limits>
#include "DataStruct.h"
#include <algorithm>

int main()
{
  using fedunov::DataStruct;
  
  std::vector<DataStruct> data;

  while (true)
  {
    DataStruct ds;
    if (std::cin >> ds)
    {
      data.push_back(ds);
    }
    else if (std::cin.eof())
    {
      break;
    }
    else
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), std::ostream_iterator< DataStruct >(std::cout, "\n"));

  return 0;
}
