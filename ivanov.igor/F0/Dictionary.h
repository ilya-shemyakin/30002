// Dictionary.h
#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <iostream>
#include <set>
#include <unordered_map>

class Dictionary
{
public:
    using iterator = std::unordered_map<std::string, int>::iterator;
    using const_iterator = std::unordered_map<std::string, int>::const_iterator;

    Dictionary(size_t bucketCount = 8);

    void insert(const std::string &key, int value);
    const_iterator find(const std::string &key) const;
    void remove(const std::string &key);

    size_t size() const;
    bool empty() const;
    float loadFactor() const;

    iterator begin();
    iterator end();
    const_iterator cbegin() const;
    const_iterator cend() const;

private:
    std::unordered_map<std::string, int> map_;
};

#endif