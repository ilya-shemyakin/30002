#include "Commands.h"

void cmd::create(Graph*& graph, std::istream& in)
{
  std::string option;
  in >> option;
  if (option == "UG") {
    delete graph;
    graph = new UndirectedGraph;
  }
  else if (option == "DG") {
    delete graph;
    graph = new DirectedGraph;
  }
  else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void cmd::add(Graph*& graph, std::istream& in)
{
  if (graph == nullptr) {
    throw std::invalid_argument("graph has not been created yet");
  }
  std::string option;
  in >> option;
  if (option == "NODE") {
    std::string index_str;
    in >> index_str;
    int index;
    try {
      index = std::stoi(index_str.c_str());
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("index is too big");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("<INVALID INDEX>");
    }
    if (index < 0) {
      throw std::invalid_argument("index must be greater than zero");
    }
    graph->addNode(index);
  }
  else if (option == "EDGE") {
    std::string option1;
    std::string option2;
    in >> option1 >> option2;
    int index1;
    int index2;
    try {
      index1 = std::stoi(option1);
      index2 = std::stoi(option2);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("index is too big");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("<INVALID INDEX>");
    }
    if (index1 < 0 || index2 < 0) {
      throw std::invalid_argument("index must be greater than zero");
    }
    graph->addEdge(index1, index2);
  }
  else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void cmd::del(Graph*& graph, std::istream& in)
{
  if (graph == nullptr) {
    throw std::invalid_argument("graph has not been created yet");
  }
  std::string option;
  in >> option;
  if (option == "NODE") {
    std::string index_str;
    in >> index_str;
    int index;
    try {
      index = std::stoi(index_str);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("index is too big");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("<INVALID INDEX>");
    }
    if (index < 0) {
      throw std::invalid_argument("index must be greater than zero");
    }
    graph->delNode(index);
  }
  else if (option == "EDGE") {
    std::string option1;
    std::string option2;
    in >> option1 >> option2;
    int index1;
    int index2;
    try {
      index1 = std::stoi(option1);
      index2 = std::stoi(option2);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("index is too big");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("<INVALID INDEX>");
    }
    if (index1 < 0 || index2 < 0) {
      throw std::invalid_argument("index must be greater than zero");
    }
    graph->delEdge(index1, index2);
  }
  else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void cmd::dfs(Graph*& graph, std::istream& in)
{
  if (graph == nullptr) {
    throw std::invalid_argument("graph has not been created yet");
  }
  std::string option;
  in >> option;
  int index;
  try {
    index = std::stoi(option);
  }
  catch (const std::out_of_range&) {
    throw std::invalid_argument("index is too big");
  }
  catch (const std::exception&) {
    throw std::invalid_argument("<INVALID INDEX>");
  }
  if (index < 0) {
    throw std::invalid_argument("index must be greater than zero");
  }
  graph->dfs(index);
  std::cout << std::endl;
}

void cmd::strong_connected(Graph*& graph, std::istream& in)
{
  if (graph == nullptr) {
    throw std::invalid_argument("graph has not been created yet");
  }
  std::string option;
  in >> option;
  if (option == "PRINT") {
    graph->strongConnectedNodes();
  }
  else if (option == "CHECK") {
    std::string option1;
    std::string option2;
    in >> option1 >> option2;
    int index1;
    int index2;
    try {
      index1 = std::stoi(option1);
      index2 = std::stoi(option2);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("index is too big");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("<INVALID INDEX>");
    }
    if (index1 < 0 || index2 < 0) {
      throw std::invalid_argument("index must be greater than zero");
    }
    std::cout << std::boolalpha << graph->isStronglyConnected(index1, index2) << std::endl;
  }
  else {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void cmd::help(Graph*& graph, std::istream& in)
{
  system("cls");
  std::cout <<
    "[CREATE UG] - create undirected graph\n" <<
    "[CREATE DG] - create directed graph\n" <<
    "[ADD NODE <index>] - create node\n" <<
    "[ADD EDGE <index1 index2>] - add edge\n" <<
    "[DEL NODE <index>] - delete node\n" <<
    "[DEL EDGE <index>] - delete edge\n" <<
    "[DFS <index>] - start deef first search from <index>\n" <<
    "[STRONG PRINT] - print all groups of strongly connected nodes\n" <<
    "[STRONG CHECK <index1 index2>] - check if index1 and index2 are strongly connected\n\n" <<
    "Press any button to go back...";
  _getch();
}
