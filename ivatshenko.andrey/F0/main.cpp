#include <iostream>
#include "frequencyDictionary.h"
#include "commands.h"
#include <string>
#include <functional>
#include <map>
#include <limits>
#include <stdexcept>

int main()
{
    frequencyDictionary dictionary;
    std::map<std::string, std::function<void(std::istream&, std::ostream&)> > cmds;
    {
        using namespace std::placeholders;
        cmds["1"] = std::bind(commands::insertWords, std::ref(dictionary), _1, _2);
        cmds["2"] = std::bind(commands::input, std::cref(dictionary), _2);
        cmds["3"] = std::bind(commands::findWord, std::cref(dictionary), _1, _2);
        cmds["4"] = std::bind(commands::deleteWord, std::ref(dictionary), _1, _2);
        cmds["5"] = std::bind(commands::help, _2);
    }
    cmds["5"](std::cin, std::cout);
    while (true)
    {
        std::string command;
        std::cin >> command;
        if (std::cin.eof())
        {
            break;
        }
        try
        {
            cmds.at(command)(std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
            std::cout << "<KEY NOT FOUND>" << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::invalid_argument& e)
        {
            std::cout << e.what() << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
