#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "DataStruct.h"

int main()
{
  std::vector<DataStruct> dataStructVector;
  DataStruct ds;

  // Используем std::copy для копирования данных из входного потока
  std::istream_iterator<DataStruct> in_begin(std::cin), in_end;
  std::copy(in_begin, in_end, std::back_inserter(dataStructVector));

  // Удаляем некорректные записи, вызвавшие failbit
  dataStructVector.erase(
    std::remove_if(dataStructVector.begin(), dataStructVector.end(),
      [](const DataStruct& ds) {
        std::istringstream iss;
        iss.str(ds.key3);
        return iss.fail();
      }),
    dataStructVector.end());

  // Сортируем данные
  std::sort(dataStructVector.begin(), dataStructVector.end());

  // Используем std::copy для вывода данных
  std::ostream_iterator<DataStruct> out_begin(std::cout, "\n");
  std::copy(dataStructVector.begin(), dataStructVector.end(), out_begin);

  return 0;
}
