#ifndef COMMANDS_H
#define COMMANDS_H

#include <unordered_map>
#include <functional>

#include "HuffmanTree.h"

namespace cmd
{
    void code(const std::string& fileName, HuffmanTree& huffmanTree, std::istream& in,
        std::ostream& out);
    void decode(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out);
    void showCodes(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out);
    void showFrequencies(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out);
    void showSize(const std::string& fileName, const HuffmanTree& huffmanTree, std::istream& in,
        std::ostream& out);
    void showEncodedSize(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out);

    inline auto getCommand(const std::string& key, const std::string& fileName,
        HuffmanTree& huffmanTree)
    {
        using namespace std::placeholders;
        std::unordered_map< std::string,
            std::function< void(std::istream& in, std::ostream& out) > > cmd =
        {
            {"CODE", std::bind(code, std::cref(fileName), std::ref(huffmanTree), _1, _2)},
            {"DECODE", std::bind(decode, std::cref(huffmanTree), _1, _2)},
            {"SHOW_CODES", std::bind(showCodes, std::cref(huffmanTree), _1, _2)},
            {"SHOW_FREQUENCIES", std::bind(showFrequencies, std::cref(huffmanTree), _1, _2)},
            {"SHOW_SIZE", std::bind(showSize, std::cref(fileName), std::cref(huffmanTree),
            _1, _2)},
            {"SHOW_ENCODED_SIZE", std::bind(showEncodedSize, std::cref(huffmanTree), _1, _2)}
        };
        return cmd.at(key);
    }

    void fillFreqTable(const std::string& fileName, HuffmanTree& huffmanTree);
    void fillHuffmanCodesTable(HuffmanTree& huffmanTree);
    void generateHuffmanCodes(HuffmanTree& huffmanTree, Node* root, std::string code);
    void freeMemory(Node* root);
}

#endif
