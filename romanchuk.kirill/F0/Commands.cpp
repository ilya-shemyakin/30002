#include "Commands.h"

#include <functional>

#include <algorithm>
#include "ReadEngRusDictFromFile.h"

void cmd::createDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (EngRusDicts.find(name) != EngRusDicts.cend())
  {
    throw std::runtime_error("ѕопытка создани€ двух словарей с одинаковыми названи€ми");
  }
  EngRusDicts[name] = EngRusDict();
}

void cmd::removeDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in)
{
  std::string name;
  in >> name;
  if (EngRusDicts.find(name) == EngRusDicts.cend())
  {
    throw std::runtime_error("—ловарь не найден");
  }
  EngRusDicts.erase(name);
}

void cmd::add(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  try
  {
    vector.at(name).addTranslation(key, translation);
  }
  catch (const std::invalid_argument&)
  {
    vector.at(name).addWord(key);
    vector.at(name).addTranslation(key, translation);
  }
}

void cmd::remove(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  std::string key, translation;
  in >> key >> translation;
  if (translation == "ALL")
  {
    vector.at(name).removeWord(key);
  }
  else
  {
    try
    {
      vector.at(name).removeTranslation(key, translation);
    }
    catch (const std::invalid_argument&)
    {
      throw std::runtime_error("key не найден или не соответствует формату");
    }
  }
}

void cmd::addWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  vector.at(nameFirstDict).addWordFromEngRusDict(vector[nameSecondDict]);
}

void cmd::removeWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  vector.at(nameFirstDict).removeWordFromEngRusDict(vector[nameSecondDict]);
}

void cmd::getIntersection(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.find(name) != vector.cend())
  {
    throw std::runtime_error("ѕопытка создани€ двух словарей с одинаковыми названи€ми");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector[name] = getIntersectionWithEngRusDict(vector[nameFirstDict], vector[nameSecondDict]);
}

void cmd::getDifference(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (vector.find(name) != vector.cend())
  {
    throw std::runtime_error("ѕопытка создани€ двух словарей с одинаковыми названи€ми");
  }
  in >> nameFirstDict >> nameSecondDict;
  vector[name] = getDifferenceWithEngRusDict(vector[nameFirstDict], vector[nameSecondDict]);
}

void cmd::clear(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector.at(name).clear();
}

void cmd::display(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (name == "ALL")
  {
    for (std::pair< std::string, EngRusDict > pair : vector)
    {
      out << pair.first;
      pair.second.display(out);
    }
  }
  else
  {
    if (vector.find(name) == vector.cend())
    {
      throw std::runtime_error("—ловарь не найден");
    }
    out << name;
    vector.at(name).display(out);
  }
}

void cmd::getTranslation(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  std::vector< std::string > result;
  for (std::pair< std::string, EngRusDict > pair : vector)
  {
    for (const std::string& translation : pair.second.getTranslations(key))
    {
      if (translation != "" && std::find(result.begin(), result.end(), translation) == result.end())
      {
        result.push_back(translation);
      }
    }
  }
  if (result.size() == 0)
  {
    throw std::runtime_error("ѕеревода слова не обнаружено");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void cmd::readDicts(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string pathToFile;
  std::cin >> pathToFile;
  std::unordered_map< std::string, EngRusDict > newVector = ReadEngRusDictFromFile(pathToFile);
  for (std::pair< std::string, EngRusDict > pair : newVector)
  {
    if (vector.find(pair.first) == vector.cend()) 
    {
      vector[pair.first] = pair.second;
    }
  }
}

void cmd::help(std::ostream& out)
{
  out << "1 createDict <new dictionary>\n";
  out << "2 removeDict <dictionary>\n";
  out << "3 add <dictionary> <english word> <translation>\n";
  out << "4 remove <dictionary> <english word> <ALL>/<translation>\n";
  out << "5 addWords <dictionaryIn> <dictionaryOut>\n";
  out << "6 removeWords <dictionaryIn> <dictionaryOut>\n";
  out << "7 getIntersection <new dictionary> <dictionaryOut> "
         "<dictionaryOut>\n";
  out << "8 getDifference <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "9 clear <dictionary>\n";
  out << "10 getTranslation <english word>\n";
  out << "11 readDicts <Path to the file>\n";
  out << "12 display <ALL>/<dictionary>\n";
  out << "13 help\n";
}
