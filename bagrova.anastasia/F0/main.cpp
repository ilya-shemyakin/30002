#include <iostream>
#include <string>

#include <stdexcept>

#include "Commands.h"
#include "Graph.h"

using namespace std;

int main() {
    try {
        Graph g;

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

    return 0;
}
