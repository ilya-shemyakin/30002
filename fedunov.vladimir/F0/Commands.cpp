#include "commands.h"
#include "Colors.h"
#include <iomanip>

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

void commands::printMenu(std::ostream& out)
{
  const std::string top_bottom_line(50, '-');

  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  out << WHITE << "|" << YELLOW << " Feel free to pick any option: " << std::setw(24) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  
  out << WHITE << "|" << YELLOW << " 1. INSERT" << std::setw(45) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  
  out << WHITE << "|" << YELLOW << " 2. TOP THREE OUT" << std::setw(38) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  
  out << WHITE << "|" << YELLOW << " 3. FIND WORD" << std::setw(42) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
 
  out << WHITE << "|" << YELLOW << " 4. DELETE" << std::setw(45) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  
  out << WHITE << "|" << YELLOW << " 6. FAQ" << std::setw(48) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
  
  out << WHITE << "|" << RED << " 7. CTRL+Z for EXIT" << std::setw(36) << WHITE << "|" << "\n";
  out << WHITE << "+" << top_bottom_line << "+" << "\n";
}