#include "Commands.h"

#include <sstream>
#include <iterator>
#include <vector>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
#include <functional>

#include "InputFormat.h"

using namespace std::placeholders;

bool convertToSize(const std::string& str, size_t& value) {
    try {
        value = std::stoi(str);
        if (value < 0) {
            return false;
        }
    }
    catch (const std::exception&) {
        return false;
    }
    return true;
}

bool processArea(const std::string& arg, std::vector<Polygon>& data) {
    // EVEN|ODD|MEAN|<num-of-vertexes:size_t>
    size_t num = 0;
<<<<<<< HEAD
=======
	
>>>>>>> 05c101b (Fixed the build errors and rolling back one change.)
    if (arg == "EVEN") {
        auto op = [](double init, const Polygon& p) {
            return init + (p.points.size() % 2 == 0 ? p.area() : 0);
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) << '\n';
    }
    else if (arg == "ODD") {
        auto op = [](double init, const Polygon& p) {
            return init + (p.points.size() % 2 != 0 ? p.area() : 0);
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) << '\n';
    }
    else if (arg == "MEAN") {
        auto op = [](double init, const Polygon& p) {
            return init + p.area();
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) / data.size() << '\n';
    }
    else if (convertToSize(arg, num)) {
        auto op = [num](double init, const Polygon& p) {
            return init + (p.points.size() == num ? p.area() : 0);
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) << '\n';
    }
    else {
        return false;
    }
    return true;
}

bool processMax(const std::string& arg, std::vector<Polygon>& data) {
    // AREA|VERTEXES
    if (arg == "AREA") {
        auto it = max_element(data.cbegin(), data.cend(), [](const Polygon& p1, const Polygon& p2) {
            return p1.area() < p2.area();
        });
        std::cout << it->area() << '\n';
    }
    else if (arg == "VERTEXES") {
        auto it = max_element(data.cbegin(), data.cend(), [](const Polygon& p1, const Polygon& p2) {
            return p1.points.size() < p2.points.size();
        });
        std::cout << it->points.size() << '\n';
    }
    else {
        return false;
    }
    return true;
}

bool processMin(const std::string& arg, std::vector<Polygon>& data) {
    // AREA|VERTEXES
    if (arg == "AREA") {
        auto it = min_element(data.cbegin(), data.cend(), [](const Polygon& p1, const Polygon& p2) {
            return p1.area() < p2.area();
        });
        std::cout << it->area() << '\n';
    }
    else if (arg == "VERTEXES") {
        auto it = min_element(data.cbegin(), data.cend(), [](const Polygon& p1, const Polygon& p2) {
            return p1.points.size() < p2.points.size();
        });
        std::cout << it->points.size() << '\n';
    }
    else {
        return false;
    }
    return true;
}

bool processCount(const std::string& arg, std::vector<Polygon>& data) {
    // EVEN|ODD|<num-of-vertexes:size_t>
    size_t num = 0;

    auto checkParity = [](int number, int parity) {
        return number % 2 == parity;
    };

    auto isOdd = std::bind(checkParity, _1, 1);
    auto isEven = std::bind(checkParity, _1, 0);

    if (arg == "EVEN") {
        std::cout << std::count_if(data.cbegin(), data.cend(), [&isEven](const Polygon& p) {
            return isEven(p.points.size());
        });
    }
    else if (arg == "ODD") {
        std::cout << std::count_if(data.cbegin(), data.cend(), [&isOdd](const Polygon& p) {
            return isOdd(p.points.size() % 2);
        });
    }
    else if (convertToSize(arg, num)) {
        auto op = [num](double init, const Polygon& p) {
            return init + (p.points.size() == num ? 1 : 0);
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0, op);
    }
    else {
        return false;
    }
    std::cout << '\n';
    return true;
}

bool processLessArea(const std::string& arg, std::vector<Polygon>& data) {
    // <Polygon>
    std::istringstream iss(arg);
    Polygon poly;
    iss >> poly;
    if (iss) {
        double s = poly.area();
        std::cout << std::count_if(data.cbegin(), data.cend(), [s](const Polygon& p) {
            return p.area() < s;
        });
    }
    else {
        return false;
    }
    std::cout << '\n';
    return true;
}

bool processIntersection(const std::string& arg, std::vector<Polygon>& data) {
    // <Polygon>
    std::istringstream iss(arg);
    Polygon poly;
    iss >> poly;
    if (iss) {
        auto cond = [&](const Polygon& p) {
            return poly.intersect(p);
            };
        size_t res = std::count_if(data.cbegin(), data.cend(), cond);
        std::cout << res << '\n';
    }
    else {
        return false;
    }
    return true;
}

void process(const std::string& cmd_string, std::vector<Polygon>& data) {
    std::istringstream iss(cmd_string);
    iss >> std::noskipws;
    std::string cmd, arg;
    iss >> cmd >> DelimiterIO{ ' ' };
    std::getline(iss, arg);
    iss >> DelimiterIO{ '\n' };

    bool res = false;
    if (cmd == "AREA") {
        res = processArea(arg, data);
    }
    else if (cmd == "MAX") {
        res = processMax(arg, data);
    }
    else if (cmd == "MIN") {
        res = processMin(arg, data);
    }
    else if (cmd == "COUNT") {
        res = processCount(arg, data);
    }
    else if (cmd == "LESSAREA") {
        res = processLessArea(arg, data);
    }
    else if (cmd == "INTERSECTIONS") {
        res = processIntersection(arg, data);
    }
    else {
        res = false;
    }

    if (!res) {
        std::cout << "<INVALID COMMAND>\n";
    }
}
