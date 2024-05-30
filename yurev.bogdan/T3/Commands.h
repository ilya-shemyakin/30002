// Commands.h
#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <functional>

#include "Polygon.h"

namespace yurev
{
    void area(const std::vector<Polygon> &data, std::istream &in, std::ostream &out);
    void min(const std::vector<Polygon> &data, std::istream &in, std::ostream &out);
    void max(const std::vector<Polygon> &data, std::istream &in, std::ostream &out);
    void count(const std::vector<Polygon> &data, std::istream &in, std::ostream &out);
    void rects(std::istream &in, std::ostream &out);
    void intersections(const std::vector<Polygon> &data, std::istream &in, std::ostream &out);

    using predicate_t = std::function<bool(const Polygon &)>;
    namespace detail
    {
        double accAreaIf(double val, const Polygon &rhs, predicate_t pred);
        double accAreaMean(double val, const Polygon &rhs, std::size_t size);
    }
}

#endif // COMMANDS_H_
