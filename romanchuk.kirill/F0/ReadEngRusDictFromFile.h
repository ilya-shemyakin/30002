#ifndef READENGRUSDICTFROMFILE_H
#define READENGRUSDICTFROMFILE_H

#include <fstream>
#include <sstream>
#include "EngRusDict.h"

std::vector< EngRusDict > ReadEngRusDictFromFile(std::string pathToFile)
{
  std::ifstream file(pathToFile);
  if (!file.is_open())
  {
    throw std::invalid_argument("Ошибка при чтении файла");
  }
  std::vector< EngRusDict > EngRusDicts;
  std::string name;
  while (getline(file, name))
  {
    EngRusDict newErd(name);
    std::string words;
    while (std::getline(file, words) && !words.empty())
    {
      std::stringstream ss(words);
      std::string eng, rus;
      std::getline(ss, eng, ':');
      try
      {
        newErd.addWord(eng);
      }
      catch (const std::invalid_argument&)
      {
        continue;
      }
      try
      {
        while (std::getline(ss, rus, ',') && !rus.empty())
        {
          rus.erase(0, 1);
          newErd.addTranslation(eng, rus);
        }
      }
      catch (const std::invalid_argument&)
      {
        newErd.removeWord(eng);
      }
    }
    EngRusDicts.push_back(newErd);
  }
  file.close();
  return EngRusDicts;
}

#endif // !READENGRUSDICTFROMFILE_H
