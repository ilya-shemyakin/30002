#include "DirectedGraph.h"

void DirectedGraph::addNode(int index)
{
  if (searchNode(index)) {
    throw std::invalid_argument("ERROR: attempt to create already existing node");
  }
  aj_list_.push_back(std::vector<int> {index});
}

bool DirectedGraph::searchNode(int index) const
{
  return std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [index](const std::vector<int>& v) {
      return (v.at(0) == index);
    }
  ) != aj_list_.end();
}

void DirectedGraph::addEdge(int src, int dest)
{
  if (!searchNode(src) || !searchNode(dest)) {
    throw std::invalid_argument("ERROR: one of the elements does not exist");
  }
  if (searchEdge(src, dest)) {
    throw std::invalid_argument("ERROR: attempt to create already existing edge");
  }
  if (src == dest) {
    throw std::invalid_argument("ERROR: element cannot be connected to itself");
  }

  (*std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [src](const std::vector<int>& v) {
      return (v.at(0) == src);
    }
  )).push_back(dest);
}

bool DirectedGraph::searchEdge(int src, int dest) const
{
  if (!searchNode(src) || !searchNode(dest)) {
    throw std::invalid_argument("ERROR: one of the elements does not exist");
  }
  if (src == dest) {
    throw std::invalid_argument("ERROR: node can't be connected to itself");
  }
  const std::vector<int>& v_t = *std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [src](const std::vector<int>& v) {
      return v.at(0) == src;
    }
  );
  return std::find(
    v_t.begin(), v_t.end(), dest
  ) != v_t.end();
}

void DirectedGraph::delEdge(int src, int dest)
{
  if (!searchNode(src) || !searchNode(dest)) {
    throw std::invalid_argument("ERROR: one of the elements does not exist");
  }
  if (!searchEdge(src, dest)) {
    throw std::invalid_argument("ERROR: such edge does not exist");
  }

  std::vector<int>& v_t1 = *std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [src](const std::vector<int>& v) {
      return (v.at(0) == src);
    }
  );
  std::remove(v_t1.begin(), v_t1.end(), dest);
  v_t1.pop_back();
}

void DirectedGraph::delNode(int index)
{
  if (!searchNode(index)) {
    throw std::invalid_argument("ERROR: attempt to delete a non-existent node");
  }
  for (int i = 0; i < aj_list_.size(); i++) {
    if (aj_list_.at(i).at(0) != index && searchEdge(aj_list_.at(i).at(0), index)) {
      std::remove(aj_list_.at(i).begin(), aj_list_.at(i).end(), index);
      aj_list_.at(i).pop_back();
    }
  }

  auto v_t = std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [index](const std::vector<int>& v) {
      return (v.at(0) == index);
    }
  );
  (*v_t).clear();
  aj_list_.erase(v_t);
}

void DirectedGraph::print() const
{
  for (std::vector<int>v : aj_list_) {
    std::cout << "[";
    for (int n : v) {
      std::cout << n;
      if (n == v.at(0)) {
        std::cout << "]";
      }
      if (n != v.at(v.size() - 1)) {
        std::cout << "->";
      }
    }
    std::cout << std::endl;
  }
}

DirectedGraph::~DirectedGraph()
{
  for (std::vector<int>v : aj_list_) {
    v.clear();
  }
  aj_list_.clear();
}

void DirectedGraph::dfs(int start_index) const
{
  if (!searchNode(start_index)) {
    throw std::invalid_argument("ERROR: start index for DFS does not exist");
  }
  std::vector<int>visited;
  dfs(start_index, visited, 1);
}

void DirectedGraph::strongConnectedNodes() const
{
  if (aj_list_.size() == 0) {
    std::cout << "ERROR: attempt to find strongly connected nodes in empty graph";
  }
  auto check_vector = [](const std::vector<int>& v, int val) {
    for (int n : v) {
      if (n == val) {
        return true;
      }
    }
    return false;
    };
  std::vector<int>strong_somponent;
  std::vector<int>visited_strong;
  std::vector<int>visited;
  for (std::vector<int>v : aj_list_) {
    if (check_vector(visited_strong, v.at(0))) {
      continue;
    }
    strong_somponent.push_back(v.at(0));
    for (std::vector<int>v2 : aj_list_) {
      if (v.at(0) != v2.at(0) && isStronglyConnected(v.at(0), v2.at(0))) {
        strong_somponent.push_back(v2.at(0));
      }
    }
    for (int n : strong_somponent) {
      std::cout << n << " ";
      visited_strong.push_back(n);
    }
    std::cout << std::endl;
    strong_somponent.clear();
  }
}

bool DirectedGraph::isStronglyConnected(int index1, int index2) const
{
  if (!searchNode(index1) || !searchNode(index2)) {
    throw std::invalid_argument("ERROR: attempt to check strong connection between un-existent nodes");
  }
  auto check_vector = [](const std::vector<int>& v, int val) {
    for (int n : v) {
      if (n == val) {
        return true;
      }
    }
    return false;
    };
  std::vector<int>visited1;
  std::vector<int>visited2;
  dfs(index1, visited1, 0);
  dfs(index2, visited2, 0);
  return (check_vector(visited1, index2) && check_vector(visited2, index1));
}

void DirectedGraph::dfs(int index, std::vector<int>& visited, bool ifPrint) const
{
  auto check_vector = [](const std::vector<int>& v, int val) {
    for (int n : v) {
      if (n == val) {
        return true;
      }
    }
    return false;
    };
  if (check_vector(visited, index)) {
    return;
  }
  if (ifPrint) {
    std::cout << index << " ";
  }
  visited.push_back(index);
  const std::vector<int>& aj_list_t = *std::find_if(
    aj_list_.begin(), aj_list_.end(),
    [index](const std::vector<int>v) {
      return (v.at(0) == index);
    }
  );
  if (aj_list_t.size() != 0) {
    for (int n : aj_list_t) {
      if (!check_vector(visited, n)) {
        dfs(n, visited, ifPrint);
      }
    }
  }
}

std::ostream& operator<<(std::ostream& out, const DirectedGraph& graph)
{
  for (std::vector<int>v : graph.aj_list_) {
    out << "[";
    for (int n : v) {
      out << n;
      if (n == v.at(0)) {
        out << "]";
      }
      if (n != v.at(v.size() - 1)) {
        out << "->";
      }
    }
    out << std::endl;
  }
  return out;
}
