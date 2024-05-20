#include "DisjointSetUnion.h"

DisjointSetUnion::DisjointSetUnion(int size) {
    p_.resize(size);
    for (int i = 0; i < size; ++i) {
        p_[i] = i;
    }
    r_ = std::vector<int>(size, 1);
}

int DisjointSetUnion::p(int v) {
    return p_[v] == v ? v : p_[v] = p(p_[v]);
}

void DisjointSetUnion::unite(int v1, int v2) {
    v1 = p(v1);
    v2 = p(v2);
    if (r_[v1] > r_[v2]) {
        std::swap(v1, v2);
    }
    p_[v1] = v2;
    r_[v2] += r_[v1];
}

int DisjointSetUnion::size() const {
    return static_cast<int>(p_.size());
}

std::ostream& operator<<(std::ostream& out, DisjointSetUnion& dsu) {
    for (size_t k = 0; k < dsu.p_.size(); ++k) {
        out << "{ ";
        for (size_t i = 0; i < dsu.p_.size(); ++i) {
            if (dsu.p(i) == static_cast<int>(k)) {
                out << i << " ";
            }
        }
        out << "} ";
    }
    return out;
}
