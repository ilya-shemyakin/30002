#include "Graph.h"
#include "InputFormat.h"
#include "Exceptions.h"
#include "DisjointSetUnion.h"

#include <fstream>

#include <algorithm>
#include <numeric>
#include <iterator>

#include <map>

bool Graph::load(const std::string& fileName) {
    std::ifstream file;
    file.open(fileName);
    if (!file.is_open()) {
        throw std::invalid_argument("Not such file!\n");
    }

    int nV=0, v,nE=0;
    file >> nV;
    for (int i = 0; i < nV; ++i) {
        file >> v;
        vertices_.insert(v);
    }

    file >> nE;

    while (!file.eof()) {
        std::copy(
            std::istream_iterator<Edge>(file),
            std::istream_iterator<Edge>(),
            back_inserter(edges_)
        );

        if (file.fail()) {
            bool eofFlag = file.eof();
            file.clear();
            if (eofFlag) {
                file.setstate(std::ios::eofbit);
            }
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    file.close();
    return (static_cast<int>(vertices_.size()) == nV && static_cast<int>(edges_.size()) == nE);
}

bool Graph::isEmpty() const {
    return edges_.empty();
}

bool Graph::containVertex(int v) const {
    return vertices_.count(v) > 0;
}

void Graph::insertVertex(int v) {
    vertices_.insert(v);
}

void Graph::removeVertex(int v) {
    vertices_.erase(v);
    auto it = std::remove_if(edges_.begin(), edges_.end(), [v](const Edge& edge) {
        return edge.first == v || edge.second == v;
        });
    edges_.erase(it, edges_.end());
}

bool Graph::containEdge(const Edge& edge) const {
    return std::any_of(edges_.begin(), edges_.end(),
        [edge](const Edge& e) {
            return (Edge{e.first,e.second,e.weight} == Edge{edge.first,edge.second,edge.weight});
        });
};

bool Graph::insertEdge(const Edge& edge) {
    if (vertices_.count(edge.first) > 0 && vertices_.count(edge.second) > 0) {
        edges_.push_back(edge);
    }
    else {
        return false;
    }
    return true;
}

void Graph::removeEdge(const Edge& edge) {
    edges_.erase(
        std::remove(edges_.begin(), edges_.end(), edge),
        edges_.end());
}

int Graph::weightEdges() const {
    auto op = [](int init, const Edge& e) {
        return init + e.weight;
        };
    return std::accumulate(edges_.cbegin(), edges_.cend(), 0, op);
}

struct EdgeCompare {
    bool operator()(const Edge& e1, const Edge& e2) const {
        return e1.weight < e2.weight;
    }
};

Graph Graph::kruskal() const {
    std::vector<Edge> edges = edges_;
    std::sort(edges.begin(), edges.end(), EdgeCompare{});

    DisjointSetUnion dsu(vertices_.size());
    Graph mst;
    for (const Edge& e : edges) {
        int v1 = e.first, v2 = e.second;
        if (dsu.p(v1) != dsu.p(v2)) {
            dsu.unite(v1, v2);
            mst.insertVertex(v1);
            mst.insertVertex(v2);
            mst.insertEdge(e);
        }
    }

    if (mst.vertices_.size() < vertices_.size()) {
        throw MstException("The graph is not linked");
    }

    return mst;
}

Graph Graph::prima() const {
    if (vertices_.empty()) {
        throw MstException("The graph is empty");
    }

    std::map<int, std::multiset<Edge>> g;
    for (const Edge& e : edges_) {
        g[e.first].insert(e);
        g[e.second].insert(Edge(e.second, e.first, e.weight));
    }

    std::multiset<Edge, EdgeCompare> q;

    int v = *vertices_.begin();
    std::set<int> visited{ v };

    Graph mst;
    do {
        for (auto e : g.at(v)) {
            int u = e.second;
            if (visited.count(u) == 0) {
                q.insert(e);
            }
        }

        Edge e = *q.begin();
        q.erase(q.begin());

        if (visited.count(e.second) == 0) {
            mst.insertVertex(e.first);
            mst.insertVertex(e.second);
            mst.insertEdge(e);

            v = e.second;
            visited.insert(v);
        }
    } while (!q.empty());

    if (mst.vertices_.size() < vertices_.size()) {
        throw MstException("The graph is not linked");
    }

    return mst;
}

std::ostream& operator<<(std::ostream& out, const Graph& graph) {
    auto& edges = graph.edges_;
    auto& vertices = graph.vertices_;
    out << "Graph:\n";
    out << "Vertices: ";
    copy(vertices.begin(), vertices.end(), std::ostream_iterator<int>(out, " "));
    out << "\nEdges:\n";
    copy(edges.begin(), edges.end(), std::ostream_iterator<Edge>(out, "\n"));
    return out;
}
