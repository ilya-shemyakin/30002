#include "Commands.h"

#include <functional>

#include <algorithm>
#include "ReadEngRusDictFromFile.h"

void cmd::createDict(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  if (subcmd::containsEngRusDict(vector, name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  EngRusDict newErd(name);
  vector.push_back(newErd);
}

void cmd::removeDict(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector.erase(vector.begin() + subcmd::findIndexDict(vector, name));
}

void cmd::add(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  size_t i = subcmd::findIndexDict(vector, name);
  std::string key, translation;
  in >> key >> translation;
  try
  {
    vector[i].addTranslation(key, translation);
  }
  catch (const std::invalid_argument&)
  {
    vector[i].addWord(key);
    vector[i].addTranslation(key, translation);
  }
}

void cmd::remove(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  bool flag = true;
  in >> name;
  size_t i = subcmd::findIndexDict(vector, name);
  std::string key, translation;
  in >> key >> translation;
  if (translation == "ALL")
  {
    vector[i].removeWord(key);
  }
  else
  {
    try
    {
      vector[i].removeTranslation(key, translation);
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
  size_t i = subcmd::findIndexDict(vector, nameFirstDict);
  size_t j = subcmd::findIndexDict(vector, nameSecondDict);
  vector[i].addWordFromEngRusDict(vector[j]);
}

void cmd::removeWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string nameFirstDict, nameSecondDict;
  in >> nameFirstDict >> nameSecondDict;
  size_t i = subcmd::findIndexDict(vector, nameFirstDict);
  size_t j = subcmd::findIndexDict(vector, nameSecondDict);
  vector[i].removeWordFromEngRusDict(vector[j]);
}

void cmd::getIntersection(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (subcmd::containsEngRusDict(vector, name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  in >> nameFirstDict >> nameSecondDict;
  size_t i = subcmd::findIndexDict(vector, nameFirstDict);
  size_t j = subcmd::findIndexDict(vector, nameSecondDict);
  vector.push_back(getIntersectionWithEngRusDict(name, vector[i], vector[j]));
}

void cmd::getDifference(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name, nameFirstDict, nameSecondDict;
  in >> name;
  if (subcmd::containsEngRusDict(vector, name))
  {
    throw std::runtime_error("Попытка создания двух словарей с одинаковыми названиями");
  }
  in >> nameFirstDict >> nameSecondDict;
  size_t i = subcmd::findIndexDict(vector, nameFirstDict);
  size_t j = subcmd::findIndexDict(vector, nameSecondDict);
  vector.push_back(getDifferenceWithEngRusDict(name, vector[i], vector[j]));
}

void cmd::clear(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string name;
  in >> name;
  vector[subcmd::findIndexDict(vector, name)].clear();
}

void cmd::display(std::unordered_map< std::string, EngRusDict >, std::istream& in, std::ostream& out)
{
  std::string name;
  in >> name;
  if (name == "ALL")
  {
    for (EngRusDict& erd : vector)
    {
      erd.display(out);
    }
  }
  else
  {
    vector[subcmd::findIndexDict(vector, name)].display(out);
  }
}

void cmd::getTranslation(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out)
{
  std::string key;
  std::cin >> key;
  std::vector< std::string > result;
  for (EngRusDict& erd : vector)
  {
    for (const std::string& translation : erd.getTranslations(key))
    {
      if (translation != "" && std::find(result.begin(), result.end(), translation) == result.end())
      {
        result.push_back(translation);
      }
    }
  }
  if (result.size() == 0)
  {
    throw std::runtime_error("Перевода слова не обнаружено");
  }
  std::copy(result.begin(), result.end(), std::ostream_iterator< std::string >(out, "\n"));
}

void cmd::readDicts(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in)
{
  std::string pathToFile;
  std::cin >> pathToFile;
  std::vector< EngRusDict > newVector = ReadEngRusDictFromFile(pathToFile);
  for (const EngRusDict& erd : newVector)
  {
    if (!subcmd::containsEngRusDict(vector, erd.getName()))
    {
      vector.push_back(erd);
    }
  }
}

void cmd::help(std::ostream& out)
{
  out << "1. createDict <new dictionary>\n";
  out << "2. removeDict <dictionary>\n";
  out << "3. add <dictionary> <english word> <translation>\n";
  out << "4. remove <dictionary> <english word> <ALL>/<translation>\n";
  out << "5. addWords <dictionaryIn> <dictionaryOut>\n";
  out << "6. removeWords <dictionaryIn> <dictionaryOut>\n";
  out << "7. getIntersection <new dictionary> <dictionaryOut> "
         "<dictionaryOut>\n";
  out << "8. getDifference <new dictionary> <dictionaryOut> <dictionaryOut>\n";
  out << "9. clear <dictionary>\n";
  out << "10. getTranslation <english word>\n";
  out << "11. readDicts <Path to the file>\n";
  out << "12. display <ALL>/<dictionary>\n";
  out << "13. help\n";
}
