#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <vector>

#include "DataStruct.h"

int main()
{
  using maltsev::DataStruct;
  std::vector< DataStruct > data;
  std::istringstream iss(
    "(:key1 8ull:key2 0xF1:key3 \"Let madness release you\":)\n"
  );

  while (!std::cin.eof())
  {
    std::copy(
      std::istream_iterator< DataStruct >(std::cin),
      std::istream_iterator< DataStruct >(),
      std::back_inserter(data)
    );
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::sort(data.begin(), data.end());

  std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
  );
  return 0;
}
