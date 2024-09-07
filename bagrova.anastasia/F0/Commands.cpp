#include "Commands.h"
#include "InputFormat.h"
#include "StreamGuard.h"

#include <sstream>

#include <iterator>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
#include <functional>

#include <vector>

using namespace std::placeholders;

bool convertToSize(const std::string& str, int& value) {
    std::istringstream iss(str);
    iss >> value;
    if (!iss || iss.rdbuf()->in_avail() > 0) {
        return false;
    }
    return true;
}

bool convertToEdge(const std::string& str, Edge& edge) {
    std::istringstream iss(str);
    iss >> edge;
    if (!iss || iss.rdbuf()->in_avail() > 0) {
        return false;
    }
    return true;
}

void invalidCommandMessage() {
    std::cout << "<INVALID COMMAND>\n";
}

bool processPrint(const std::string& arg, const Graph& graph) {
    if (!arg.empty()) {
        return false;
    }
    std::cout << graph;
    return true;
}

bool processContainVertex(const std::string& arg, const Graph& graph) {
    int num;
    bool res = convertToSize(arg, num);

    if (graph.isEmpty() || !res) {
        return false;
    }
    std::cout << std::boolalpha << graph.containVertex(num) << '\n';
    return true;
}
bool processContainEdge(const std::string& arg, const Graph& graph) {
    Edge edge;
    if (!convertToEdge(arg, edge)) {
        return false;
    }

    if (graph.isEmpty()) {
        return false;
    }

    std::cout << std::boolalpha << graph.containEdge(edge) << '\n';
    return true;
}

bool processInsertVertex(const std::string& arg, Graph& graph) {
    int num;
    bool res = convertToSize(arg, num);

    if (!res) {
        return false;
    }

    if (graph.containVertex(num)) {
        std::cout << "Graph already contains vertex " << num << "\n";
    }
    else {
        graph.insertVertex(num);
    }

    return true;
}

bool processInsertEdge(const std::string& arg, Graph& graph) {
    Edge edge;
    if (!convertToEdge(arg, edge)) {
        return false;
    }

    return graph.insertEdge(edge);
}

bool processRemoveVertex(const std::string& arg, Graph& graph) {
    int num;
    bool res = convertToSize(arg, num);

    if (!res) {
        return false;
    }

    graph.removeVertex(num);
    return true;
}

bool processRemoveEdge(const std::string& arg, Graph& graph) {
    Edge edge;
    if (!convertToEdge(arg, edge)) {
        return false;
    }

    graph.removeEdge(edge);
    return true;
}

bool processWeight(const Graph& graph) {
    std::cout << graph.weightEdges() << '\n';
    return true;
}

bool processPrim(Graph& graph) {
    Graph mst = graph.prima();
    std::cout << "MST = " << mst;
    std::cout << "Result cost = " << mst.weightEdges() << '\n';
    return true;
}

bool processKruskal(Graph& graph) {
    Graph mst = graph.kruskal();
    std::cout << "MST = " << mst;
    std::cout << "Result cost = " << mst.weightEdges() << '\n';
    return true;
}

void readCommand(const std::string& cmd_string, std::string& cmd, std::string& arg) {
    std::istringstream iss(cmd_string);
    iss >> std::noskipws;

    iss >> cmd >> DelimiterIO{ ' ' };
    std::getline(iss, arg);
    iss >> DelimiterIO{ '\n' };
}

bool process(const std::string& cmd_string, Graph& data) {
    std::string cmd, arg;
    readCommand(cmd_string, cmd, arg);

    bool res = false;
    if (cmd == "PRINT" && arg == "") {
        res = processPrint(arg, data);
    }
    else if (cmd == "CONTAIN_VERTEX") {
        res = processContainVertex(arg, data);
    }
    else if (cmd == "CONTAIN_EDGE") {
        res = processContainEdge(arg, data);
    }
    else if (cmd == "INSERT_VERTEX") {
        res = processInsertVertex(arg, data);
    }
    else if (cmd == "INSERT_EDGE") {
        res = processInsertEdge(arg, data);
    }
    else if (cmd == "REMOVE_VERTEX") {
        res = processRemoveVertex(arg, data);
    }
    else if (cmd == "REMOVE_EDGE") {
        res = processRemoveEdge(arg, data);
    }
    else if (cmd == "WEIGHT" && arg == "") {
        res = processWeight(data);
    }
    else if (cmd == "PRIM" && arg == "") {
        res = processPrim(data);
    }
    else if (cmd == "KRUSKAL" && arg == "") {
        res = processKruskal(data);
    }
    else {
        res = false;
    }

    return res;
}
