#include <iostream>
#include <string>
#include <iomanip>

#include <vector>
#include <iterator>
#include <limits>

#include <algorithm>
#include <numeric>

#include "Polygon.h"
#include "InputFormat.h"
#include "Commands.h"
#include "StreamGuard.h"

int main(int argc, char** argv) {
    std::string fileName;
    if (argc > 1) {
        fileName = argv[1];
    }
    else {
        std::cerr << "Error: program needs filename as cmd line arg!\n";
        return -1;
    }

    try {
        std::vector<Polygon> data;

        load(fileName, data);

        StreamGuard coutGuard(std::cout);
        std::cout << std::fixed << std::setprecision(1);

        std::string cmd;
        while (std::cin >> cmd) {
            bool res = process(cmd, data);
            if (!res) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    catch (const std::invalid_argument& ex) {
        std::cerr << ex.what();
        return -1;
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what();
        return -1;
    }
}
