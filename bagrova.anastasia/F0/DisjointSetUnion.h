#ifndef DISJOINT_SET_UNION_H
#define DISJOINT_SET_UNION_H

#include <iostream>
#include <vector>

class DisjointSetUnion {
public:
    DisjointSetUnion(int size);

    int p(int v);
    void unite(int v1, int v2);
    int size() const;

    friend std::ostream& operator<<(std::ostream& out, DisjointSetUnion& dsu);

private:
    std::vector<int> p_; // parent
    std::vector<int> r_; // rank
};

#endif
