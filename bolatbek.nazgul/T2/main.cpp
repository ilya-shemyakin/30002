#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Delimeter.hpp"
#include "DataStruct.hpp"

int main()
{
  using input_it_t = std::istream_iterator< bolatbek::DataStruct >;
  using output_it_t = std::ostream_iterator< bolatbek::DataStruct >;
  std::vector< bolatbek::DataStruct > data;
  while (!std::cin.eof())
  {
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    std::copy(input_it_t(std::cin), input_it_t(), std::back_inserter(data));
  }
  std::sort(data.begin(), data.end());
  std::copy(data.cbegin(), data.cend(), output_it_t{std::cout, "\n"});

  return 0;
}