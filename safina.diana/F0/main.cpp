#include <iostream>
#include <exception>

#include "Commands.h"
#include "HuffmanTree.h"

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");

    // Checking if the file name argurment is correct
    std::string fileName = "";
    if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        if (argc == 1)
        {
            std::cerr << "Error! File name is required as a command line argument\n";
        }
        else
        {
            std::cerr << "Error! Too many arguments. Only one is required as a file name\n";
        }
        return -1;
    }

    // Output of the menu where a user can view the list of commands
    std::cout << "Список доступных команд:\n"
        "1) CODE - закодировать сообщение из файла по алгоритму Хаффмана;\n"
        "2) DECODE {CODED MESSAGE} - раскодировать сообщение на основе составленного ранее "
        "дерева Хаффмана;\n"
        "3) SHOW_CODES - вывести таблицу кодов Хаффмана для каждого символа;\n"
        "4) SHOW_FREQUENCIES - вывести таблицу частот (весов) символов;\n"
        "5) SHOW_SIZE - вывести размер сообщения в битах, если бы использовали алгоритм "
        "кодирования с одинаковой длиной всех кодовых слов;\n"
        "6) SHOW_ENCODED_SIZE - вывести размер сообщения, закодированного по алгоритму Хаффмана, "
        "в битах\n\n";

    cmd::HuffmanTree huffmanTree;

    // Reading commands
    std::string command = "";
    while (std::cin >> command)
    {
        try
        {
            cmd::getCommand(command, fileName, huffmanTree)(std::cin, std::cout);
        }
        catch (const std::out_of_range& error)
        {
            std::cerr << "Command not found\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n'); 
        }
        catch (const std::invalid_argument& error)
        {
            std::cerr << error.what();
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
        catch (const std::exception& error)
        {
            std::cerr << error.what();
        }
    }
    cmd::freeMemory(huffmanTree.root);

    return 0;
}