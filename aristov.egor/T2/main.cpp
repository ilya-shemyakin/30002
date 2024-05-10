#include"DataStruct.h"
#include"InputFormat.h"
#include<vector>
#include<algorithm>
int main() {
  std::vector<DataStruct>dataStructV;
  while (!std::cin.eof()) {
    std::copy(std::istream_iterator<DataStruct>(std::cin),
      std::istream_iterator<DataStruct>(),
      std::back_inserter(dataStructV));

    if (std::cin.fail() && !std::cin.eof()) {
      std::cin.clear();
      std::cout << "\n[main cin.fail()]";
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
  std::sort(dataStructV.begin(), dataStructV.end());

  std::copy(dataStructV.begin(),
    dataStructV.end(),
    std::ostream_iterator<DataStruct>(std::cout, "\n"));
  return 0;
}
