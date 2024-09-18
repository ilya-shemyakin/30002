#ifndef LOCAL_H
#define LOCAL_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <iomanip>
#include <complex>
#include <algorithm>
#include <exception>

#include "structure2.h"

using DNLX::DataStruct;
int main()
{
  try
  {
    std::string input = "";

    std::vector< DataStruct > data;

    while (!std::cin.eof())
    {
      std::copy(
        std::istream_iterator< DataStruct >(std::cin),
        std::istream_iterator< DataStruct >(),
        back_inserter(data)
      );
      if (std::cin.fail() && !std::cin.eof())
      {
        std::cin.clear();
      }
    }
    std::sort(std::begin(data), std::end(data), DNLX::compareDataStruct);

    std::copy(
    std::begin(data),
    std::end(data),
    std::ostream_iterator< DataStruct >(std::cout, "\n")
    );
  }
  catch (std::exception& ex)
  {
    std::cerr << ex.what();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

#endif
