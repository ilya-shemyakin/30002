#include <iostream>
#include <string>

#include <stdexcept>

#include "Commands.h"
#include "Graph.h"

using namespace std;

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
        Graph g;

        g.load(fileName);

        std::string cmd;
        while (std::getline(std::cin, cmd)) {
            bool res = process(cmd, g);
            if (!res) {
                invalidCommandMessage();
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
