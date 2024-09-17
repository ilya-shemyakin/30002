#include<iostream>
#include<map>
#include<functional>
#include<limits>

#include"UndirectedGraph.h"
#include"DirectedGraph.h"
#include"Graph.h"
#include"Commands.h"

int main() {
  Graph* cur_graph = nullptr;
  std::map<std::string, std::function<void(std::istream&)>>cmds;
  {
    using namespace std::placeholders;
    cmds["CREATE"] = std::bind(cmd::create, std::ref(cur_graph), _1);
    cmds["ADD"] = std::bind(cmd::add, std::ref(cur_graph), _1);
    cmds["DEL"] = std::bind(cmd::del, std::ref(cur_graph), _1);
    cmds["DFS"] = std::bind(cmd::dfs, std::ref(cur_graph), _1);
    cmds["STRONG"] = std::bind(cmd::strong_connected, std::ref(cur_graph), _1);
    cmds["HELP"] = std::bind(cmd::help, std::ref(cur_graph), _1);
  }
  std::string command;
  std::string res = "";
  while (true) {
    if (command != "DFS" && command != "STRONG") {
      system("cls");
      if (cur_graph != nullptr) {
        cur_graph->print();
      }
      std::cout << "\nType \"HELP\" to see all available commands\n";
    }
    if (res != "") {
      std::cout << res << std::endl;
      res = "";
    }
    std::cin >> command;
    if (std::cin.eof()) {
      delete cur_graph;
      break;
    }
    try {
      cmds.at(command)(std::cin);
    }
    catch (std::invalid_argument& e) {
      res = e.what();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch (std::out_of_range&) {
      res = "<INVALID COMMAND>";
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
