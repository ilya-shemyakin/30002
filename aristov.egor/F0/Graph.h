#ifndef GRAPH_H
#define GRAPH_H
#include<iostream>

struct Graph {
  virtual void addNode(int index) = 0;
  virtual void addEdge(int src, int dest) = 0;
  virtual bool searchEdge(int src, int dest)const = 0;
  virtual bool searchNode(int index)const = 0;
  virtual void delEdge(int src, int dest) = 0;
  virtual void delNode(int index) = 0;
  virtual void dfs(int start_index)const = 0;
  virtual void strongConnectedNodes()const = 0;
  virtual bool isStronglyConnected(int inedex1, int index2)const = 0;
  virtual void print()const = 0;
};

#endif
