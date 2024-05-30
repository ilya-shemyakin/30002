#include "frequencyDictionary.h"

frequencyDictionary::frequencyDictionary()
{}

frequencyDictionary::frequencyDictionary(const frequencyDictionary& other)
{
    words_ = other.words_;
}

frequencyDictionary::frequencyDictionary(frequencyDictionary&& other) noexcept
{
    words_ = std::move(other.words_);
    other.words_.clear();
}

frequencyDictionary& frequencyDictionary::operator=(const frequencyDictionary& other)
{
    words_ = other.words_;
    return *this;
}

frequencyDictionary& frequencyDictionary::operator=(frequencyDictionary&& other) noexcept
{
    words_ = std::move(other.words_);
    other.words_.clear();
    return *this;
}

frequencyDictionary::~frequencyDictionary()
{
    clear();
}

void frequencyDictionary::clear()
{
    words_.clear();
}

void frequencyDictionary::insert(const std::string& str)
{
    if (isWord(str))
    {
        words_[tolower(str)] += 1;
    }
}

void frequencyDictionary::search(const std::string& str, std::ostream& out) const
{
    out << str << ": " << words_.at(str) << '\n';
}

void frequencyDictionary::deleteWord(const std::string& str, std::ostream& out)
{
    if (find(str))
    {
        words_.erase(str);
        out << "Key \"" << str << "\" was removed from dictionary.\n";
    }
    else
    {
        throw std::invalid_argument{ "Key not found." };
    }
}

bool frequencyDictionary::find(const std::string& str) const
{
    return words_.find(str) != words_.end();
}

void frequencyDictionary::findTopThree(std::ostream& out) const
{
    std::vector<std::pair<std::string, std::size_t>> data;
    std::copy(words_.begin(), words_.end(), std::back_inserter(data));
    std::sort(data.begin(), data.end(),
        [](const std::pair<std::string, std::size_t>& left, const std::pair<std::string, std::size_t>& right)
        {
            return left.second > right.second;
        }
    );
    for (std::size_t i = 0; i < data.size() && i < 3; i++)
    {
        out << data[i].first << ": " << data[i].second << '\n';
    }
}

bool frequencyDictionary::isWord(const std::string& str)
{
    std::regex pattern("^[a-zA-Z]+(?:['`][a-zA-Z]+)?(?:[a-zA-Z]+[-][a-zA-Z]+){0,2}[a-zA-Z]+");
    if (std::regex_match(str, pattern))
    {
        return true;
    }
    else if (std::regex_match(str, std::regex("^-?[0-9]+$")))
    {
        return true;
    }
    return false;
}

std::string frequencyDictionary::tolower(std::string str)
{
    using namespace std::placeholders;
    std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return std::tolower(c); });
    return str;
}
