#include "Dictionary.h"

Dictionary::Dictionary(size_t bucketCount) : map_(bucketCount)
{
}

void Dictionary::insert(const std::string& key, int value)
{
    map_[key] = value;
}

Dictionary::const_iterator Dictionary::find(const std::string& key) const
{
    return map_.find(key);
}

void Dictionary::remove(const std::string& key)
{
    map_.erase(key);
}

size_t Dictionary::size() const
{
    return map_.size();
}

bool Dictionary::empty() const
{
    return map_.empty();
}

float Dictionary::loadFactor() const
{
    return map_.load_factor();
}

Dictionary::iterator Dictionary::begin()
{
    return map_.begin();
}

Dictionary::iterator Dictionary::end()
{
    return map_.end();
}

Dictionary::const_iterator Dictionary::cbegin() const
{
    return map_.cbegin();
}

Dictionary::const_iterator Dictionary::cend() const
{
    return map_.cend();
}