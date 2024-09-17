#ifndef DIRECTEDGRAPH_H
#define DIRECTEDGRAPH_H

#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

#include"Graph.h"

class DirectedGraph:public Graph
{
public:
  DirectedGraph() {};
  void addNode(int index) override;
  bool searchNode(int index)const override;
  void addEdge(int src, int dest) override;
  bool searchEdge(int src, int dest)const override;
  void delEdge(int src, int dest) override;
  void delNode(int index) override;
  void print()const override;
  ~DirectedGraph();

  void dfs(int start_index)const;
  void strongConnectedNodes()const override;
  bool isStronglyConnected(int index1, int index2)const override;

  friend std::ostream& operator<<(std::ostream& out, const DirectedGraph& graph);
private:
  void dfs(int index, std::vector<int>& visited, bool ifPrint)const;
  std::vector<std::vector<int>> aj_list_;
};

#endif
