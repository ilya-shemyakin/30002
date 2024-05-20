#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_map>

#include "Dictionary.h"

void printTranslations(const std::set<std::string>& lst);
void printDictionary(const Dictionary& dict);


int main()
{
  std::system("chcp 1251 > nul");
  Dictionary dict;
  std::string choice, englishWord, russianWord;

  while (true)
  {
    std::cout << "\nChoose an option:\n"
      << "1. Load dictionary from file\n"
      << "2. Show dictionary statistics\n"
      << "3. Add translation\n"
      << "4. Search translation\n"
      << "5. Remove translation\n"
      << "6. Print dictionary\n"
      << "7. Exit\n"
      << "> ";
    std::getline(std::cin, choice);
    if (choice == "1")
    {
      std::string filename;
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
        if (!(std::getline(iss, englishWord, '-') && std::getline(iss, russianWord)))
        {
          std::cerr << "Failed to parse line: " << line << std::endl;
          continue;
        }
        englishWord.erase(englishWord.find_last_not_of(" ") + 1);
        russianWord.erase(0, russianWord.find_first_not_of(" "));

        dict.insert(englishWord, russianWord);
      }
      file.close();
      std::cout << "Dictionary loaded.\n";
    }
    else if (choice == "2")
    {
      std::cout << "Dictionary Size: " << dict.size() << " entries\n";
      std::cout << "Dictionary Load Factor: " << dict.loadFactor() << "%\n";
    }
    else if (choice == "3")
    {
      std::cout << "Enter English word: ";
      std::getline(std::cin, englishWord);
      std::cout << "Enter Russian translation: ";
      std::getline(std::cin, russianWord);
      dict.insert(englishWord, russianWord);
      std::cout << "Translation added.\n";
    }
    else if (choice == "4")
    {
      std::cout << "Enter English word: ";
      std::getline(std::cin, englishWord);
      auto search = dict.find(englishWord);
      std::cout << englishWord << ": ";
      if (search != dict.end())
      {
        printTranslations(search->second);
      }
      else
      {
        std::cout << "Translation not found!\n";
      }
    }
    else if (choice == "5")
    {
      std::cout << "Enter English word: ";
      std::getline(std::cin, englishWord);
      std::cout << "Enter Russian translation to remove: ";
      std::getline(std::cin, russianWord);
      dict.remove(englishWord, russianWord);
      std::cout << "Translation removed if it existed.\n";
    }
    else if (choice == "6")
    {
      printDictionary(dict);
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


void printTranslations(const std::set<std::string>& lst)
{
  auto it = lst.cbegin();
  if (it != lst.cend())
  {
    std::cout << *it;
    ++it;
  }
  while (it != lst.cend())
  {
    std::cout << ", " << *it;
    ++it;
  }
  std::cout << std::endl;
}

void printDictionary(const Dictionary& dict)
{
  const size_t entriesPerPage = 5;
  size_t totalEntries = dict.size();
  size_t totalPages = (totalEntries + entriesPerPage - 1) / entriesPerPage;
  size_t currentPage = 0;
  size_t count = 0;
  std::string choice;

  std::cout << "Dictionary contents:\n";

  for (auto it = dict.cbegin(); it != dict.cend(); ++it)
  {
    if (count % entriesPerPage == 0)
    {
      currentPage++;
      std::cout << "Page " << currentPage << " of " << totalPages << ":\n";
    }

    std::cout << it->first << ": ";
    printTranslations(it->second);

    if (++count % entriesPerPage == 0 && count != totalEntries)
    {
      std::cout << "\nPress 'Q' to quit: ";
      std::getline(std::cin, choice);

      if (choice == "Q" || choice == "q")
      {
        std::cout << "Exiting print...\n";
        break;
      }
    }
  }

  if (count % entriesPerPage != 0 || totalEntries == 0)
  {
    std::cout << "\nEnd of dictionary. Page " << currentPage << " of " << totalPages << ".\n";
  }
}
