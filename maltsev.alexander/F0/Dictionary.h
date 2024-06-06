#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <iostream>
#include <set>
#include <unordered_map>


class Dictionary
{
public:
  using iterator = std::unordered_map<std::string, std::set<std::string>>::iterator;
  using const_iterator = std::unordered_map<std::string, std::set<std::string>>::const_iterator;

  Dictionary(size_t bucketCount = 8);

  void insert(const std::string& key, const std::string& value);
  const_iterator find(const std::string& key);
  void remove(const std::string& key, const std::string& value);

  size_t size() const;
  bool empty() const;
  float loadFactor() const;

  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

private:
  std::unordered_map<std::string, std::set<std::string>> map_;
};

#endif
