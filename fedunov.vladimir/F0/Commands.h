#ifndef COMMANDS_H
#define COMMANDS_H

#include "Dictionary.h"
#include <string>
#include <iostream>
#include <functional>
#include <algorithm>
#include <cctype>

namespace commands
{
  void insertWords(frequencyDictionary& dictionary, std::istream& in, std::ostream& out);
  void input(const frequencyDictionary& dictionary, std::ostream& out);
  void findWord(const frequencyDictionary& dictionary, std::istream& in, std::ostream& out);
  void deleteWord(frequencyDictionary& dictionary, std::istream& in, std::ostream& out);
  void printMenu(std::ostream& out);
}
#endif
