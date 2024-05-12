#include <iostream>
#include <string>
#include <iomanip>

#include <vector>
#include <iterator>

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

        StreamGuard guard(std::cout);
        std::cout << std::fixed << std::setprecision(1);
        
        std::string cmd;
        while (std::getline(std::cin, cmd)) {
            process(cmd, data);
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
