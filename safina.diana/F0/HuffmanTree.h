#ifndef HUFFMAN_TREE_H
#define HUFFMAN_TREE_H

#include <unordered_map>
#include <string>

#include "Node.h"

namespace cmd
{
    struct HuffmanTree
    {
        HuffmanTree() :
            root(nullptr)
        {}

        std::unordered_map< char, int > freq;
        std::unordered_map< char, std::string > codes;
        Node* root;
    };
}

#endif
