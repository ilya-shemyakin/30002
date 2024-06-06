#include "Dictionary.h"


Dictionary::Dictionary(std::size_t bucketCount) : map_(bucketCount)
{}

void Dictionary::insert(const std::string& key, const std::string& value)
{
  map_[key].insert(value);
}

Dictionary::const_iterator Dictionary::find(const std::string& key)
{
  return map_.find(key);
}

void Dictionary::remove(const std::string& key, const std::string& value)
{
  auto search = map_.find(key);
  if (search != map_.end() && search->second.erase(value) && search->second.empty())
  {
    map_.erase(key);
  }
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
