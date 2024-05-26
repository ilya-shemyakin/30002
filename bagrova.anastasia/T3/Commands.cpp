#include "Commands.h"

#include <sstream>
#include <string>

#include <iterator>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <numeric>
#include <functional>

#include "InputFormat.h"
#include "StreamGuard.h"

using namespace std::placeholders;

bool convertToSize(const std::string& str, int& value) {
    try {
        value = std::stoi(str);
    }
    catch (const std::exception&) {
        return false;
    }
    return true;
}

void invalidCommandMessage() {
    std::cout << "<INVALID COMMAND>\n";
}

int minVertecesSizeInPolygon() {
    return 3;
}

bool processArea(std::vector<Polygon>& data) {
    // EVEN|ODD|MEAN|<num-of-vertexes:size_t>

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    std::string arg;
    std::cin >> DelimiterIO{ ' ' } >> arg >> DelimiterIO{ '\n' };
    if (!std::cin) {
        return false;
    }

    int num = 0;

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
        if (data.empty()) {
            return false;
        }

        auto op = [](double init, const Polygon& p) {
            return init + p.area();
        };
        std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) / data.size() << '\n';
    }
    else {
        bool res = convertToSize(arg, num);
        if (res) {
            if (num < minVertecesSizeInPolygon()) {
                invalidCommandMessage();
                return true;
            }

            auto op = [num](double init, const Polygon& p) {
                return init + (static_cast<int>(p.points.size()) == num ? p.area() : 0);
            };
            std::cout << std::accumulate(data.cbegin(), data.cend(), 0.0, op) << '\n';
        }
        else {
            return false;
        }
    }
    return true;
}

bool processMax(std::vector<Polygon>& data) {
    // AREA|VERTEXES

    if (data.empty()) {
        return false;
    }

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    std::string arg;
    std::cin >> DelimiterIO{ ' ' } >> arg >> DelimiterIO{ '\n' };
    if (!std::cin) {
        return false;
    }

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

bool processMin(std::vector<Polygon>& data) {
    // AREA|VERTEXES

    if (data.empty()) {
        return false;
    }

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    std::string arg;
    std::cin >> DelimiterIO{ ' ' } >> arg >> DelimiterIO{ '\n' };
    if (!std::cin) {
        return false;
    }

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

bool processCount(std::vector<Polygon>& data) {
    // EVEN|ODD|<num-of-vertexes:size_t>

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    std::string arg;
    std::cin >> DelimiterIO{ ' ' } >> arg >> DelimiterIO{ '\n' };
    if (!std::cin) {
        return false;
    }

    int num = 0;

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
    else {
        bool res = convertToSize(arg, num);
        if (res) {
            if (num < minVertecesSizeInPolygon()) {
                invalidCommandMessage();
                return true;
            }

            auto op = [num](double init, const Polygon& p) {
                return init + (static_cast<int>(p.points.size()) == num ? 1 : 0);
            };
            std::cout << std::accumulate(data.cbegin(), data.cend(), 0, op);
        }
        else {
            return false;
        }
    }
    std::cout << '\n';
    return true;
}

bool processLessArea(std::vector<Polygon>& data) {
    // <Polygon>

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    Polygon poly;
    std::cin >> DelimiterIO{ ' ' } >> poly;

    if (std::cin) {
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

bool processIntersection(std::vector<Polygon>& data) {
    // <Polygon>

    StreamGuard cinGuard(std::cin);
    std::cin >> std::noskipws;
    Polygon poly;
    std::cin >> DelimiterIO{ ' ' } >> poly;

    if (std::cin) {
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

bool process(const std::string& cmd, std::vector<Polygon>& data) {
    bool res = false;

    if (cmd == "AREA") {
        res = processArea(data);
    }
    else if (cmd == "MAX") {
        res = processMax(data);
    }
    else if (cmd == "MIN") {
        res = processMin(data);
    }
    else if (cmd == "COUNT") {
        res = processCount(data);
    }
    else if (cmd == "LESSAREA") {
        res = processLessArea(data);
    }
    else if (cmd == "INTERSECTIONS") {
        res = processIntersection(data);
    }
    else {
        res = false;
    }

    if (!res) {
        invalidCommandMessage();
    }

    return res;
}
