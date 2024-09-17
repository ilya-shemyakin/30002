#ifndef COMMANDS_H
#define COMMANDS_H

#include<string>
#define NOMINMAX
#include<windows.h>
#include<conio.h>

#include"Graph.h"
#include"UndirectedGraph.h"
#include"DirectedGraph.h"

namespace cmd
{
  void create(Graph*& graph, std::istream& in);
  void add(Graph*& graph, std::istream& in);
  void del(Graph*& graph, std::istream& in);
  void dfs(Graph*& graph, std::istream& in);
  void strong_connected(Graph*& graph, std::istream& in);
  void help(Graph*& graph, std::istream& in);
}

#endif
