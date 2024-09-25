#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <regex>
#include <cctype>

class frequencyDictionary
{
private:
  std::map < std::string, std::size_t > words_;
  std::string tolower(std::string str);
  bool isWord(const std::string& str);
public:
  frequencyDictionary();
  frequencyDictionary(const frequencyDictionary& other);
  frequencyDictionary(frequencyDictionary&& other) noexcept;
  frequencyDictionary& operator=(const frequencyDictionary& other);
  frequencyDictionary& operator=(frequencyDictionary&& other) noexcept;
  ~frequencyDictionary();
  void clear();
  void insert(const std::string& str);
  void search(const std::string& str, std::ostream& out) const;
  void deleteWord(const std::string& str, std::ostream& out);
  bool find(const std::string& str) const;
  void findTopThree(std::ostream& out) const;
};

#endif
