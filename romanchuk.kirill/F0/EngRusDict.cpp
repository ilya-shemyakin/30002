#include "EngRusDict.h"

#include <algorithm>
#include <functional>

EngRusDict::EngRusDict()
{}

EngRusDict::EngRusDict(const EngRusDict& other)
{
  words_ = other.words_;
}

EngRusDict::EngRusDict(EngRusDict&& other) noexcept:
  words_(std::move(other.words_))
{
  other.clear();
}

EngRusDict::~EngRusDict()
{
  clear();
}

void EngRusDict::clear()
{
  words_.clear();
}

std::set< std::string > EngRusDict::getTranslations(const std::string& eng) const
{
  return words_.at(eng);
}

size_t EngRusDict::getCountWords() const
{
  return words_.size();
}

size_t EngRusDict::getCountTranslations(const std::string& eng) const
{
  return words_.at(eng).size();
}

void EngRusDict::display(std::ostream& out) const
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    for (const std::pair< std::string, std::set< std::string > >& pair : words_)
    {
      out << "\n" << pair.first << ": ";
      if (!pair.second.empty())
      {
        auto it = pair.second.begin();
        out << *it;
        ++it;
        for (; it != pair.second.end(); ++it)
        {
          out << ", " << *it;
        }
      }
    }
    out << "\n";
  }
}

void EngRusDict::addTranslation(const std::string& eng, const std::string& translation)
{
  if (!containsOnlyRussianLetters(translation))
  {
    throw std::invalid_argument("ѕеревод слова должно состо€ть только из кирилицы");
  }
  words_[eng].insert(getLettersToLower(translation));
}

void EngRusDict::removeTranslation(const std::string& eng, const std::string& translation)
{
  if (!containsOnlyRussianLetters(translation))
  {
    throw std::invalid_argument("ѕеревод слова должно состо€ть только из кирилицы");
  }
  words_[eng].erase(words_.at(eng).find(getLettersToLower(translation)));
}

void EngRusDict::addWord(const std::string& eng)
{
  if (!containsOnlyEnglishLetters(eng))
  {
    throw std::invalid_argument("јнглийские слова должны состо€ть только из латиницы");
  }
  words_[getLettersToLower(eng)] = std::set< std::string >();
}

void EngRusDict::removeWord(const std::string& eng)
{
  words_.erase(eng);
}

void EngRusDict::addWordFromEngRusDict(const EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > >& pair : other.words_)
  {
    try
    {
      words_.at(pair.first).insert(pair.second.begin(), pair.second.end());
    }
    catch (const std::out_of_range&)
    {
      words_.insert(pair);
    }
  }
}

void EngRusDict::removeWordFromEngRusDict(const EngRusDict& other)
{
  for (const std::pair< std::string, std::set< std::string > >& pair : other.words_)
  {
    try
    {
      words_.at(pair.first).erase(pair.second.begin(), pair.second.end());
    }
    catch (const std::out_of_range&)
    {
      continue;
    }
  }
}

EngRusDict& EngRusDict::operator=(const EngRusDict& other)
{
  words_ = other.words_;
  return *this;
}

std::string EngRusDict::getLettersToLower(std::string word)
{
  using namespace std::placeholders;
  std::transform(word.begin(), word.end(), word.begin(), std::bind(std::tolower, _1));
  return word;
}

bool EngRusDict::containsOnlyRussianLetters(const std::string& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!(c >= 'а' && c <= '€' || c >= 'ј' && c <= 'я'))
    {
      result = false;
      break;
    }
  }
  return result;
}

bool EngRusDict::containsOnlyEnglishLetters(const std::string& word) const
{
  bool result = true;
  for (const char& c : word)
  {
    if (!std::isalpha(c))
    {
      result = false;
      break;
    }
  }
  return result;
}

EngRusDict getIntersectionWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict newDict;
  for (const std::pair< std::string, std::set< std::string > >& pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) != erd1.words_.end())
    {
      newDict.words_[pair.first];
      const std::set<std::string>& translations = erd1.words_.at(pair.first);
      newDict.words_.at(pair.first).insert(translations.begin(), translations.end());
    }
  }
  return newDict;
}

EngRusDict getDifferenceWithEngRusDict(const EngRusDict& erd1, const EngRusDict& erd2)
{
  EngRusDict newDict;
  for (const std::pair< std::string, std::set< std::string > >& pair : erd2.words_)
  {
    if (erd1.words_.find(pair.first) == erd1.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  for (const std::pair< std::string, std::set< std::string > >& pair : erd1.words_)
  {
    if (erd2.words_.find(pair.first) == erd2.words_.end())
    {
      newDict.words_[pair.first] = pair.second;
    }
  }
  return newDict;
}
