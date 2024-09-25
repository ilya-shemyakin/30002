#include <iostream>
#include <sstream>
#include <string>
#include "Dictionary.h"

void printFrequencyDictionary(const Dictionary& dict)
{
    std::cout << "Frequency Dictionary contents:\n";
    for (auto it = dict.cbegin(); it != dict.cend(); ++it)
    {
        std::cout << it->first << ": " << it->second << std::endl;
    }
}

int main() {
    Dictionary dict; 
    std::string input;

    while (true) {
        std::cout << "\nChoose an option:\n"
            << "1. Show dictionary statistics\n"
            << "2. Add word\n"
            << "3. Search word\n"
            << "4. Remove word\n"
            << "5. Print dictionary\n"
            << "6. Exit\n"
            << "> ";
        std::getline(std::cin, input);

        if (std::cin.eof()) { 
            break;
        }

        std::istringstream iss(input);
        std::string command, word;
        int value;

        iss >> command;

        if (command == "1") {
            std::cout << "Dictionary size: " << dict.size() << " words." << std::endl;
            std::cout << "Load factor: " << dict.loadFactor() << std::endl;
        }
        else if (command == "2") {
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
        else if (command == "3") {
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
        else if (command == "4") {
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
        else if (command == "5") {

            if (dict.empty()) {
                std::cout << "Dictionary is empty." << std::endl;
            }
            printFrequencyDictionary(dict);
        }
        else if (command == "6") {
            std::cout << "Exiting program." << std::endl;
            break;
        }
        else {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return EXIT_SUCCESS;
}
