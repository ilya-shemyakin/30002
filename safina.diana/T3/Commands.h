#ifndef COMMANDS_H
#define COMMANDS_H

#include <unordered_map>
#include <functional>

#include "Polygon.h"

namespace cmd
{
    // Functions from the task
    void area(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);
    void max(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);
    void min(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);
    void count(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);
    void perms(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);
    void maxseq(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out);

    // Using the Gauss's area formula to determine area of a simple polygon
    double getShapeArea(const shapes::Polygon& shape);
    // Auxiliary function that generates pairs of indexes for the area formula
    std::vector< std::pair< int, int > > generatePairIndexes(size_t shapeSize);

    // Function that calls functions according to the input
    inline auto getCommand(const std::vector< shapes::Polygon >& shapes, std::string key)
    {
        using namespace std::placeholders;
        std::unordered_map < std::string,
            std::function< void(std::istream& in, std::ostream& out) > > cmd =
        {
            {"AREA", std::bind(area, std::cref(shapes), _1, _2)},
            {"MAX", std::bind(max, std::cref(shapes), _1, _2)},
            {"MIN", std::bind(min, std::cref(shapes), _1, _2)},
            {"COUNT", std::bind(count, std::cref(shapes), _1, _2)},
            {"PERMS", std::bind(perms, std::cref(shapes), _1, _2)},
            {"MAXSEQ", std::bind(maxseq, std::cref(shapes), _1, _2)}
        };
        return cmd.at(key);
    }
}

#endif
