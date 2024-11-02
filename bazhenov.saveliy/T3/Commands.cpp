#include "Commands.h"
#include "Polygon.h"
#include <algorithm>
#include <string>
#include <cmath>
#include <iomanip>
#include <functional>
#include <numeric>
#include <vector>
#include "StreamGuard.h"

const std::string ERROR_405 = "<INVALID COMMAND>"; // 405 Method Not Allowed

void rightShapes(const std::vector<Polygon>& vecPoly) {
    std::cout << std::count_if(vecPoly.cbegin(), vecPoly.cend(), rightAngle) << '\n';
}

void count(const std::vector<Polygon>& vecPoly) {
    std::string str;
    std::cin >> str;

    auto calcPolygons = [](const Polygon& poly, std::size_t rest, std::size_t vertexes) -> bool {
            return ((poly.points.size() % 2 == rest) || (rest == 2 && poly.points.size() == vertexes));
        };


    if (str == "EVEN")
        std::cout << std::count_if(vecPoly.begin(), vecPoly.end(),
            std::bind(calcPolygons, std::placeholders::_1, 0, 0)) << '\n';

    else if (str == "ODD")
        std::cout << std::count_if(vecPoly.begin(), vecPoly.end(),
            std::bind(calcPolygons, std::placeholders::_1, 1, 0)) << '\n';

    else if (std::all_of(str.begin(), str.end(), isdigit) && stoi(str) > 2)
        std::cout << std::count_if(vecPoly.begin(), vecPoly.end(),
            std::bind(calcPolygons, std::placeholders::_1, 2, stoi(str))) << '\n';

    else
        throw ERROR_405;
}

void area(const std::vector<Polygon>& vecPoly) {
    std::string str;
    std::cin >> str;

    auto sumArea = [](double answer, const Polygon& vecPoly, std::size_t rest, std::size_t vertexes) {
            if ((vecPoly.points.size() % 2 == rest) || (rest == 2 && vecPoly.points.size() == vertexes) || (rest == 3))
                answer += vecPoly.area();
            return answer;
        };

    if (str == "MEAN" && vecPoly.size() != 0) {
        std::cout << std::accumulate(vecPoly.cbegin(), vecPoly.cend(), 0.0,
            std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 3, 0)) / vecPoly.size() << std::endl;
    }
    else if (str == "EVEN") {
        std::cout << std::accumulate(vecPoly.cbegin(), vecPoly.cend(), 0.0,
            std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 0, 0)) << '\n';
    }
    else if (str == "ODD") {
        std::cout << std::accumulate(vecPoly.cbegin(), vecPoly.cend(), 0.0,
            std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 1, 0)) << '\n';
    }
    else if (std::all_of(str.begin(), str.end(), isdigit) && stoi(str) > 2) {
        std::cout << std::accumulate(vecPoly.cbegin(), vecPoly.cend(), 0.0,
            std::bind(sumArea, std::placeholders::_1, std::placeholders::_2, 2, stoi(str))) << '\n';
    }
    else {
        throw ERROR_405;
    }
}

//void echo(std::vector<Polygon>& vecPoly) {
//    Polygon poly;
//    std::cin >> poly;
//
//    if (std::cin.fail() || std::cin.get() != '\n')
//        throw ERROR_405;
//
//    std::vector<Polygon> result;
//    int count = 0;
//    for (const Polygon& el : vecPoly) {
//        result.push_back(el);
//        if (el == poly) {
//            count++;
//            result.push_back(el);
//        }
//    }
//
//    vecPoly = std::move(result);
//    std::cout << count << '\n';
//}


void echo(std::vector<Polygon>& vecPoly) {
    Polygon poly;
    std::cin >> poly;

    if (std::cin.fail() || std::cin.get() != '\n')
        throw ERROR_405;

    int count = 0;
    std::vector<std::vector<Polygon>> result;

    std::transform(vecPoly.begin(), vecPoly.end(), std::back_inserter(result),
        [&poly, &count](const Polygon& el) {
            if (el == poly) {
                count++;
                return std::vector<Polygon>{el, el};
            }
            else {
                return std::vector<Polygon>{el};
            }
        }
    );

    vecPoly = std::accumulate(result.begin(), result.end(), std::vector<Polygon>(),
        [](std::vector<Polygon>& acc, const std::vector<Polygon>& vec) {
            acc.insert(acc.end(), vec.begin(), vec.end());
            return acc;
        }
    );

    // test print
    //for (const Polygon& el : vecPoly) {
    //    std::cout << el << '\n';
    //}

    std::cout << count << '\n';
}

void min(const std::vector<Polygon>& vecPoly) {
    if (vecPoly.empty())
        throw ERROR_405;

    std::string str;
    std::cin >> str;

    if (str == "VERTEXES") {
        std::vector<std::size_t> sizes(vecPoly.size());

        std::cout << std::min_element(vecPoly.begin(), vecPoly.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() < b.points.size();
            }
        )->points.size() << '\n';
    }
    else if (str == "AREA")
        std::cout << std::min_element(vecPoly.begin(), vecPoly.end())->area() << '\n';
    else
        throw ERROR_405;
}

void max(const std::vector<Polygon>& vecPoly) {
    if (vecPoly.empty())
        throw ERROR_405;

    std::string str;
    std::cin >> str;

    if (str == "VERTEXES") {
        std::vector<std::size_t> sizes(vecPoly.size());

        std::cout << std::max_element(vecPoly.begin(), vecPoly.end(),
            [](const Polygon& a, const Polygon& b) {
                return a.points.size() > b.points.size();
            }
        )->points.size() << '\n';
    }
    else if (str == "AREA")
        std::cout << std::max_element(vecPoly.begin(), vecPoly.end())->area() << '\n';
    else
        throw ERROR_405;
}
