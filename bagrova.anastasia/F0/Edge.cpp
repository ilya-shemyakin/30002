#include "Edge.h"

Edge::Edge() :
    weight(0) {};

Edge::Edge(int v1, int v2, int w) :
    std::pair<int, int>(v1, v2),
    weight(w) {}

bool Edge::operator==(const Edge& other) const {
    return (((weight == other.weight) && (first == other.first && second == other.second))
        || (first == other.second && second == other.first && weight == other.weight));
}
bool Edge::operator<(const Edge& other) const {
    return (weight < other.weight);
}

std::ostream& operator<<(std::ostream& out, const Edge& edge) {
    out << edge.first << " - " << edge.second
        << " (" << edge.weight << ")";
    return out;
}
