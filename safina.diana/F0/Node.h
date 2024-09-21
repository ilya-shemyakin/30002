#ifndef NODE_H
#define NODE_H

namespace cmd
{
    // Óחוכ הונוגא Õאפפלאםא
    struct Node
    {
        char symbol;
        int freq;
        Node* left;
        Node* right;

        Node(char symbol, int freq) :
            symbol(symbol),
            freq(freq),
            left(nullptr),
            right(nullptr)
        {}
    };
}

#endif
