#include "commands.h"

void commands::insertWords(frequencyDictionary& dictionary, std::istream& in, std::ostream& out)
{
    out << "Start reading. Type Ctrl + Z to stop.\n";
    std::string word = "";
    while (in >> word)
    {
        if (in.eof())
        {
            break;
        }
        if (word[word.size() - 1] == '.' || word[word.size() - 1] == ',' || word[word.size() - 1] == ';' ||
            word[word.size() - 1] == ':' || word[word.size() - 1] == '!' || word[word.size() - 1] == '?')
        {
            word.erase(word.size() - 1);
        }
        dictionary.insert(word);
    }
    in.clear();
    out << "Reading are stopped\n";
}

void commands::input(const frequencyDictionary& dictionary, std::ostream& out)
{
    dictionary.findTopThree(out);
}

void commands::findWord(const frequencyDictionary& dictionary, std::istream& in, std::ostream& out)
{
    std::string str = "";
    in >> str;
    if (str == "")
    {
        throw std::invalid_argument{ "<INVALID ARGUMENT>" };
    }
    dictionary.search(str, out);
}

void commands::deleteWord(frequencyDictionary& dictionary, std::istream& in, std::ostream& out)
{
    std::string str = "";
    in >> str;
    if (str == "")
    {
        throw std::invalid_argument{ "<INVALID ARGUMENT>" };
    }
    dictionary.deleteWord(str, out);
}

void commands::help(std::ostream& out)
{
    out << "COMMAND LIST:\n";
    out << "1 >>> READ WORDS;\n";
    out << "2 >>> INPUT TOP THREE;\n";
    out << "3 >>> FIND WORD <WORD>;\n";
    out << "4 >>> DELETE WORD <WORD>;\n";
    out << "5 >>> COMMAND LIST;\n";
}
