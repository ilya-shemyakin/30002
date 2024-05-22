#ifndef COMMANDS_H
#define COMMANDS_H

#include "EngRusDict.h"
#include <unordered_map>
#include <vector>

namespace cmd // command
{
  void createDict(std::unordered_map< std::string, EngRusDict >& EngRusDicts, std::istream& in);
  void removeDict(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void add(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void remove(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void addWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void removeWords(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void getIntersection(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void getDifference(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void clear(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void display(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out);
  void getTranslation(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in, std::ostream& out);
  void readDicts(std::unordered_map< std::string, EngRusDict >& vector, std::istream& in);
  void help(std::ostream& out);
} // namespace cmd

#endif // !COMMANDS_H
