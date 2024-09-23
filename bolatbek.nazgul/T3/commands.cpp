#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iterator>

struct Point {
    int x, y;

    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

struct Polygon {
    std::vector<Point> points;

    double area() const {
        if (points.size() < 3) return 0.0;
        double area = 0.0;
        for (size_t i = 0; i < points.size(); ++i) {
            size_t j = (i + 1) % points.size();
            area += points[i].x * points[j].y - points[j].x * points[i].y;
        }
        return std::abs(area) / 2.0;
    }

    bool operator==(const Polygon& other) const {
        return points == other.points;
    }
};

std::vector<Polygon> readPolygons(const std::string& filename) {
    std::vector<Polygon> polygons;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int vertexCount;
        char ch;
        if (!(iss >> vertexCount) || vertexCount < 3) continue;

        Polygon polygon;
        for (int i = 0; i < vertexCount; ++i) {
            int x, y;
            if (!(iss >> ch >> x >> ch >> y >> ch)) break;
            polygon.points.push_back({x, y});
        }

        if (polygon.points.size() == static_cast<size_t>(vertexCount)) {
            polygons.push_back(polygon);
        }
    }
    return polygons;
}

void handleCommand(const std::string& command, std::vector<Polygon>& polygons) {
    std::istringstream iss(command);
    std::string cmd;
    iss >> cmd;

    if (cmd == "AREA") {
        std::string type;
        iss >> type;

        if (type == "EVEN") {
            double totalArea = 0.0;
            for (const auto& polygon : polygons) {
                if (polygon.points.size() % 2 == 0) {
                    totalArea += polygon.area();
                }
            }
            std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
        } else if (type == "ODD") {
            double totalArea = 0.0;
            for (const auto& polygon : polygons) {
                if (polygon.points.size() % 2 != 0) {
                    totalArea += polygon.area();
                }
            }
            std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
        } else if (type == "MEAN") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            double totalArea = 0.0;
            for (const auto& polygon : polygons) {
                totalArea += polygon.area();
            }
            std::cout << std::fixed << std::setprecision(1) << (totalArea / polygons.size()) << std::endl;
        } else {
            try {
                int vertexCount = std::stoi(type);
                double totalArea = 0.0;
                for (const auto& polygon : polygons) {
                    if (polygon.points.size() == vertexCount) {
                        totalArea += polygon.area();
                    }
                }
                std::cout << std::fixed << std::setprecision(1) << totalArea << std::endl;
            } catch (...) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    } else if (cmd == "MAX") {
        std::string type;
        iss >> type;

        if (type == "AREA") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            double maxArea = 0.0;
            for (const auto& polygon : polygons) {
                maxArea = std::max(maxArea, polygon.area());
            }
            std::cout << std::fixed << std::setprecision(1) << maxArea << std::endl;
        } else if (type == "VERTEXES") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            size_t maxVertexes = 0;
            for (const auto& polygon : polygons) {
                maxVertexes = std::max(maxVertexes, polygon.points.size());
            }
            std::cout << maxVertexes << std::endl;
        } else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    } else if (cmd == "MIN") {
        std::string type;
        iss >> type;

        if (type == "AREA") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }
            double minArea = polygons.front().area();
            for (const auto& polygon : polygons) {
                minArea = std::min(minArea, polygon.area());
            }
            std::cout << std::fixed << std::setprecision(1) << minArea << std::endl;
        } else if (type == "VERTEXES") {
            if (polygons.empty()) {
                std::cout << "<INVALID COMMAND>" << std::endl;
                return;
            }

            size_t minVertexes = polygons.front().points.size();
            for (const auto& polygon : polygons) {
                minVertexes = std::min(minVertexes, polygon.points.size());
            }
            std::cout << minVertexes << std::endl;
        } else {
            std::cout << "<INVALID COMMAND>" << std::endl;
        }
    } else if (cmd == "COUNT") {
        std::string type;
        iss >> type;

        if (type == "EVEN") {
            size_t count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
                return polygon.points.size() % 2 == 0;
            });

            std::cout << count << std::endl;
        } else if (type == "ODD") {
            size_t count = std::count_if(polygons.begin(), polygons.end(), [](const Polygon& polygon) {
                return polygon.points.size() % 2 != 0;
            });
            std::cout << count << std::endl;
        } else {
            try {
                int vertexCount = std::stoi(type);
                size_t count = std::count_if(polygons.begin(), polygons.end(), [vertexCount](const Polygon& polygon) {
                    return polygon.points.size() == vertexCount;
                });
                std::cout << count << std::endl;
            } catch (...) {
                std::cout << "<INVALID COMMAND>" << std::endl;
            }
        }
    } else if (cmd == "ECHO") {
        std::string polyStr;
        std::getline(iss, polyStr);
        std::istringstream polyIss(polyStr);

        int vertexCount;
        char ch;
        polyIss >> vertexCount;
        Polygon echoPolygon;
        for (int i = 0; i < vertexCount; ++i) {
            int x, y;
            polyIss >> ch >> x >> ch >> y >> ch;
            echoPolygon.points.push_back({x, y});
        }

        size_t initialSize = polygons.size();
        for (auto it = polygons.begin(); it != polygons.end(); ++it) {
            if (*it == echoPolygon) {
                it = polygons.insert(it + 1, echoPolygon);
            }
        }
        std::cout << polygons.size() - initialSize << std::endl;
    } else if (cmd == "MAXSEQ") {
        std::string polyStr;
        std::getline(iss, polyStr);
        std::istringstream polyIss(polyStr);

        int vertexCount;
        char ch;
        polyIss >> vertexCount;
        Polygon maxSeqPolygon;
        for (int i = 0; i < vertexCount; ++i) {
            int x, y;
            polyIss >> ch >> x >> ch >> y >> ch;
            maxSeqPolygon.points.push_back({x, y});
        }

        size_t maxSeq = 0;
        size_t currentSeq = 0;
        for (const auto& polygon : polygons) {
            if (polygon == maxSeqPolygon) {
                currentSeq++;
            } else {
                maxSeq = std::max(maxSeq, currentSeq);
                currentSeq = 0;
            }
        }
        maxSeq = std::max(maxSeq, currentSeq);
        std::cout << maxSeq << std::endl;
    } else {
        std::cout << "<INVALID COMMAND>" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Error: No input file provided." << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::vector<Polygon> polygons = readPolygons(filename);

    std::string command;
    while (std::getline(std::cin, command)) {
        handleCommand(command, polygons);
    }

    return 0;
}
