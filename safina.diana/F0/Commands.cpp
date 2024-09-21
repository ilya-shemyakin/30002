#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

#include "Commands.h"
#include "PQComparator.h"
#include "StreamGuard.h"
#include "InputFormats.h"

namespace cmd
{
    void code(const std::string& fileName, HuffmanTree& huffmanTree, std::istream& in,
        std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ '\n' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        if (huffmanTree.codes.empty())
        {
            fillFreqTable(fileName, huffmanTree);
            fillHuffmanCodesTable(huffmanTree);
        }

        std::ifstream file(fileName);
        if (!file.is_open())
        {
            throw std::invalid_argument("Error! Unable to open the file\n");
        }

        std::ofstream file2("result.txt");
        if (!file2.is_open())
        {
            throw std::invalid_argument("Error! Unable to open the file\n");
        }

        while (!file.eof())
        {
            char symbol = file.get();
            if (symbol != -1)
            {
                out << huffmanTree.codes[symbol];
                file2 << huffmanTree.codes[symbol];
            }
        }
        out << '\n';

        file.close();
        file2.close();
    }

    void decode(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ ' ' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        Node* path = huffmanTree.root;
        char symbol = '\0';

        while (in >> symbol)
        {
            if (symbol == '0')
            {
                path = path->left;
            }
            else if (symbol == '1')
            {
                path = path->right;
            }
            else
            {
                if (symbol == '\n')
                {
                    break;
                }
                throw std::invalid_argument("Error! Incorrect coded message is given\n");
            }

            if (path->symbol != '\0')
            {
                out << path->symbol;
                path = huffmanTree.root;
            }
        }
        out << '\n';
    }

    void showCodes(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ '\n' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        std::for_each(huffmanTree.codes.cbegin(), huffmanTree.codes.cend(),
            [&out](const auto& pair)
            {
                out << pair.first << " : " << pair.second << '\n';
            }
        );
    }

    void showFrequencies(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ '\n' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        std::for_each(huffmanTree.freq.cbegin(), huffmanTree.freq.cend(),
            [&out](const auto& pair)
            {
                out << pair.first << " : " << pair.second << '\n';
            }
        );
    }

    void showSize(const std::string& fileName, const HuffmanTree& huffmanTree, std::istream& in,
        std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ '\n' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        std::ifstream file(fileName, std::ios::ate);
        if (!file.is_open())
        {
            throw std::invalid_argument("Error! Unable to open the file\n");
        }

        std::ifstream::pos_type size = file.tellg();
        file.close();
        if (huffmanTree.root != nullptr)
        {
            out << static_cast<int>(size) * ceil(log2(huffmanTree.codes.size())) << " bit\n";
        }
        else
        {
            throw std::exception("Error! You need to run 'CODE' to build a Huffman's tree\n");
        }
    }

    void showEncodedSize(const HuffmanTree& huffmanTree, std::istream& in, std::ostream& out)
    {
        formatsIO::StreamGuard guard(in);
        in >> std::noskipws;

        in >> formatsIO::DelimiterIO{ '\n' };
        if (in.fail())
        {
            throw std::invalid_argument("Incorrect command is given\n");
        }

        std::ifstream file("result.txt", std::ios::ate);
        if (!file.is_open())
        {
            throw std::exception("Error! You need to code a message - unable to open"
                "the file with a coded message\n");
        }

        std::ios::pos_type size = file.tellg();
        if (huffmanTree.root != nullptr)
        {
            out << static_cast<int>(size) << " bit\n";
        }
        else
        {
            throw std::exception("Error! You need to run 'CODE' to build a Huffman's tree\n");
        }
    }

    void fillFreqTable(const std::string& fileName, HuffmanTree& huffmanTree)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            throw std::invalid_argument("Error! Unable to open the file\n");
        }

        while (!file.eof())
        {
            char symbol = file.get();
            if (symbol != -1)
            {
                huffmanTree.freq[symbol]++;
            }
        }

        file.close();
    }

    void fillHuffmanCodesTable(HuffmanTree& huffmanTree)
    {
        std::priority_queue< Node*, std::vector< Node* >, PQComparator > queue;
        for (const auto& pair : huffmanTree.freq)
        {
            queue.push(new Node(pair.first, pair.second));
        }

        while (queue.size() > 1)
        {
            Node* left = queue.top();
            queue.pop();

            Node* right = queue.top();
            queue.pop();

            Node* newNode = new Node('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;
            queue.push(newNode);
        }

        huffmanTree.root = queue.top();
        generateHuffmanCodes(huffmanTree, huffmanTree.root, "");
    }

    void generateHuffmanCodes(HuffmanTree& huffmanTree, Node* root, std::string code)
    {
        if (root == nullptr)
        {
            return;
        }

        if (root->symbol != '\0')
        {
            huffmanTree.codes[root->symbol] = code;
        }

        generateHuffmanCodes(huffmanTree, root->left, code + "0");
        generateHuffmanCodes(huffmanTree, root->right, code + "1");
    }

    void freeMemory(Node* root)
    {
        if (root == nullptr)
        {
            return;
        }
        freeMemory(root->left);
        freeMemory(root->right);
        delete root;
    }
}
