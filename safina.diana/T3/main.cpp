#include <iostream>
#include <string>
#include <iomanip>

#include "Polygon.h"
#include "fillVector.h"
#include "StreamGuard.h"
#include "Commands.h"

int main(int argc, char* argv[])
{
    // Checking if the file name argurment is correct
    std::string fileName = "";
    if (argc == 2)
    {
        fileName = argv[1];
    }
    else
    {
        if (argc == 1)
        {
            std::cerr << "Error! File name is required as a command line argument\n";
        }
        else
        {
            std::cerr << "Error! Too many arguments. Only one is required as a file name\n";
        }
        return -1;
    }

    // Filling a vector with shapes from the file
    std::vector< shapes::Polygon > shapes;
    try
    {
        shapes = shapes::fillVector(fileName);
    }
    catch (const std::invalid_argument& error)
    {
        std::cerr << error.what();
        return -1;
    }

    // User input with some command support
    shapes::StreamGuard guard(std::cout);
    std::cout << std::fixed << std::setprecision(1);
    std::string command = "";
    while (std::cin >> command)
    {
        try
        {
            cmd::getCommand(shapes, command)(std::cin, std::cout);
            std::cout << '\n';
        }
        catch (...)
        {
            std::cout << "<INVALID COMMAND>\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }

    return 0;
}
