#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Node.h"

namespace cmd
{
    struct PQComparator
    {
        bool operator()(const Node* left, const Node* right)
        {
            return left->freq > right->freq;  // Min frequency is priority
        }
    };
}

#endif
