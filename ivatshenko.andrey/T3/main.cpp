#include <iostream>
#include <map>
#include <limits>
#include <functional>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include "commands.h"
#include "figures.h"
#include "io.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Error: Expected 1 command-line argument, but got " << argc - 1 << ".\n";
        return EXIT_FAILURE;
    }
    std::string fileName = argv[1];
    std::ifstream file(fileName);
    if (!file)
    {
        std::cerr << "Error: file didn't open\n";
        return EXIT_FAILURE;
    }

    std::cout << std::setprecision(1) << std::fixed;
    std::vector<ivatshenko::Polygon> polygons;
    while (!file.eof())
    {
        std::copy(
            std::istream_iterator<ivatshenko::Polygon>(file),
            std::istream_iterator<ivatshenko::Polygon>(),
            std::back_inserter(polygons)
        );
        if (!file.eof() && file.fail())
        {
            file.clear();
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::map<std::string, std::function< void(std::istream&, std::ostream&) > > commands;
    {
        using namespace std::placeholders;
        commands["AREA"] = std::bind(ivatshenko::area, polygons, _1, _2);
        commands["MAX"] = std::bind(ivatshenko::max, polygons, _1, _2);
        commands["MIN"] = std::bind(ivatshenko::min, polygons, _1, _2);
        commands["COUNT"] = std::bind(ivatshenko::count, polygons, _1, _2);
        commands["INFRAME"] = std::bind(ivatshenko::inFrame, polygons, _1, _2);
        commands["RMECHO"] = std::bind(ivatshenko::rmecho, polygons, _1, _2);
    }
    std::string cmd;
    while (std::cin >> cmd)
    {
        try
        {
            commands.at(cmd)(std::cin, std::cout);
        }
        catch (const std::out_of_range&)
        {
            std::cerr << "<INVALID COMMAND>\n";
            std::cin.clear();
        }
        catch (const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cin.clear();
        }
    }
}
