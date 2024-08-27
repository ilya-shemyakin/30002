#include<iostream>
#include<vector>
#include<map>
#include<functional>

#include"Polygon.h"
#include"ReadFromFile.h"
#include"Commands.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cout << "ERROR: incorrect input, expected 1 command-line argument\n";
    return 1;
  }
  std::vector< Polygon > arr_poly = read_polygons_from_file(argv[1]);

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > cmds;
  {
    using namespace std::placeholders;
    cmds["AREA"] = std::bind(cmd::area, std::cref(arr_poly), _1, _2);
    cmds["MAX"] = std::bind(cmd::max, std::cref(arr_poly), _1, _2);
    cmds["MIN"] = std::bind(cmd::min, std::cref(arr_poly), _1, _2);
    cmds["COUNT"] = std::bind(cmd::count, std::cref(arr_poly), _1, _2);
    cmds["LESSAREA"] = std::bind(cmd::lessarea, std::cref(arr_poly), _1, _2);
    cmds["MAXSEQ"] = std::bind(cmd::maxseq, std::cref(arr_poly), _1, _2);
  }

  std::string command;
  while (std::cin >> command) {
    if (std::cin.eof()) {
      break;
    }
    try {
      cmds.at(command)(std::cin, std::cout);
    }
    catch (const std::out_of_range&) {
      std::cout << "<INVALID COMMAND>\n";
      clean_istream(std::cin);
    }
    catch (const std::invalid_argument) {
      std::cout << "<INVALID COMMAND>\n";
      clean_istream(std::cin);
    }
  }
  return 0;
}
