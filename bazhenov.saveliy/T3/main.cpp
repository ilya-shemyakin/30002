#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <exception>
#include <string>
#include <sstream>
#include <iterator>
#include <iomanip>
#include "Commands.h"
#include <vector>
#include <numeric>
#include "Polygon.h"
#include "InputFormatters.h"
#include "Commands.h"
#include "StreamGuard.h"

const std::string INVALID_COMAND = "<INVALID COMMAND>";


int main(int argc, char* argv[]) {
    std::string fileName;
    if (argc > 1) {
        fileName = argv[1];
    }
    else {
        std::cerr << "Error: It is required to specify the file name and path to the file as command line arguments\n";
        return EXIT_FAILURE;
    }

    std::vector<Polygon> vec;
    try {
        load(fileName, vec);
    }
    catch (const std::invalid_argument& ex) {
        std::cerr << ex.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const std::exception& ex) {
        std::cerr << "An error occurred: " << ex.what() << '\n';
        return EXIT_FAILURE;
    }

    while (!std::cin.eof()) {
        StreamGuard guard(std::cin);
        std::cin.clear();
        std::string comand;
        std::cin >> comand;
        try {
            StreamGuard guard(std::cout);
            std::cout << std::setprecision(1) << std::fixed;
            if (comand == "AREA")
                area(vec);
            else if (comand == "MIN")
                min(vec);
            else if (comand == "MAX")
                max(vec);
            else if (comand == "COUNT")
                count(vec);
            else if (comand == "ECHO")
                echo(vec);
            else if (comand == "RIGHTSHAPES")
                rightShapes(vec);
            else if (!std::cin.eof()) {
                throw INVALID_COMAND;
            }
        }
        catch (const std::string ex) {
            std::cout << ex << '\n';
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
