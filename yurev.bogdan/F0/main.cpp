#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>

#include "Dictionary.h"

void printFrequencyDictionary(const Dictionary &dict)
{
    std::cout << "Frequency Dictionary contents:\n";
    for (auto it = dict.cbegin(); it != dict.cend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

int main()
{
    std::system("chcp 1251 > nul");
    Dictionary dict;
    std::string choice, filename, word;

    while (true)
    {
        std::cout << "\nChoose an option:\n"
                  << "1. Load text from file\n"
                  << "2. Show dictionary statistics\n"
                  << "3. Add word\n"
                  << "4. Search word\n"
                  << "5. Remove word\n"
                  << "6. Print dictionary\n"
                  << "7. Exit\n"
                  << "> ";
        if (!std::getline(std::cin, choice))
        {
            std::cout << "Exiting program.\n";
            break;
        }
        if (choice == "1")
        {
            std::cout << "Enter filename: ";
            std::getline(std::cin, filename);
            std::ifstream file(filename);
            if (!file.is_open())
            {
                std::cerr << "Error opening file " << filename << std::endl;
                continue;
            }

            std::string line;
            while (std::getline(file, line))
            {
                std::istringstream iss(line);
                while (iss >> word)
                {
                    std::string lowercaseWord;
                    for (char c : word)
                    {
                        lowercaseWord += std::tolower(c);
                    }
                    dict.insert(lowercaseWord, dict.find(lowercaseWord) != dict.end() ? dict.find(lowercaseWord)->second + 1 : 1);
                }
            }
            file.close();
            std::cout << "Text loaded.\n";
        }
        else if (choice == "2")
        {
            std::cout << "Dictionary Size: " << dict.size() << " words\n";
            std::cout << "Dictionary Load Factor: " << dict.loadFactor() << "%\n";
        }
        else if (choice == "3")
        {
            std::cout << "Enter word: ";
            std::getline(std::cin, word);
            std::string lowercaseWord;
            for (char c : word)
            {
                lowercaseWord += std::tolower(c);
            }
            dict.insert(lowercaseWord, dict.find(lowercaseWord) != dict.end() ? dict.find(lowercaseWord)->second + 1 : 1);
            std::cout << "Word added.\n";
        }
        else if (choice == "4")
        {
            std::cout << "Enter word: ";
            std::getline(std::cin, word);
            std::string lowercaseWord;
            for (char c : word)
            {
                lowercaseWord += std::tolower(c);
            }
            auto search = dict.find(lowercaseWord);
            std::cout << lowercaseWord << ": ";
            if (search != dict.end())
            {
                std::cout << "Found\n";
            }
            else
            {
                std::cout << "Not found\n";
            }
        }
        else if (choice == "5")
        {
            std::cout << "Enter word: ";
            std::getline(std::cin, word);
            std::string lowercaseWord;
            for (char c : word)
            {
                lowercaseWord += std::tolower(c);
            }
            dict.remove(lowercaseWord);
            std::cout << "Word removed if it existed.\n";
        }
        else if (choice == "6")
        {
            printFrequencyDictionary(dict);
        }
        else if (choice == "7")
        {
            std::cout << "Exiting program.\n";
            break;
        }
        else
        {
            std::cout << "Invalid option. Please try again.\n";
        }
    }
    return EXIT_SUCCESS;
}