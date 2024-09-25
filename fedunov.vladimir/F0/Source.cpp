// Source.cpp
// РГР
// Частотный словарь: 2-3 Дерево

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <functional>
#include <map>
#include <limits>
#include <stdexcept>

#include <csignal>
#include <windows.h>


#include "PrintMenu.h"
#include "Colors.h"
#include "Dictionary.h"
#include "Commands.h"


int main() {
  std::system("chcp 1251 > nul");
  setlocale(LC_ALL, "");
  printmenu::kursachOut();

  frequencyDictionary dictionary;
  std::map<std::string, std::function<void(std::istream&, std::ostream&)>> cmds;

  {
    using namespace std::placeholders;
    cmds["1"] = std::bind(commands::insertWords, std::ref(dictionary), _1, _2);
    cmds["2"] = std::bind(commands::input, std::cref(dictionary), _2);
    cmds["3"] = std::bind(commands::findWord, std::cref(dictionary), _1, _2);
    cmds["4"] = std::bind(commands::deleteWord, std::ref(dictionary), _1, _2);
    cmds["5"] = std::bind(commands::printMenu, _2);
  }

  cmds["5"](std::cin, std::cout);
  printmenu::runSpinnerUntilInput();

  while (true) {
    std::string command;
    std::cin >> command;
    if (std::cin.eof()) {
      break;
    }
    try {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range&) {
      std::cout << "<KEY NOT FOUND>" << '\n';
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
    catch (const std::invalid_argument& e) {
      std::cout << e.what() << '\n';
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
  }

  return EXIT_SUCCESS;
}
