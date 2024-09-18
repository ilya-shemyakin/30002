#include <iostream>
#include <iterator>
#include <fstream>
#include <functional>
#include <unordered_map>
#include <limits>

#include "Polygon.h"
#include "Commands.h"

int main(int argc, const char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: invalid argument provided!\n";
        return 1;
    }

    std::ifstream file(argv[1]);
    if (!file.is_open())
    {
        std::cerr << "Error: can't open the file!\n";
        return 2;
    }
    using namespace ivanov;
    std::vector<Polygon> polygons;

    while (!file.eof())
    {
        using input_it_t = std::istream_iterator< Polygon >;
        std::copy(input_it_t{ file }, input_it_t{}, std::back_inserter(polygons));
        if (file.fail() && !file.eof())
        {
            file.clear();
            file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }
    file.close();

    std::unordered_map<std::string, std::function<void(std::istream&, std::ostream&)>> commands;

    {
        using namespace std::placeholders;
        commands["AREA"] = std::bind(area, std::cref(polygons), _1, _2);
        commands["MAX"] = std::bind(max, std::cref(polygons), _1, _2);
        commands["MIN"] = std::bind(min, std::cref(polygons), _1, _2);
        commands["COUNT"] = std::bind(count, std::cref(polygons), _1, _2);
        commands["SAME"] = std::bind(same, std::cref(polygons), _1, _2);
        commands["RMECHO"] = std::bind(rmecho, std::ref(polygons), _1, _2);
    }

    std::string cmd;

    while (std::cin >> cmd)
    {
        try
        {
            commands.at(cmd)(std::cin, std::cout);
            std::cout << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }

    return 0;
}
