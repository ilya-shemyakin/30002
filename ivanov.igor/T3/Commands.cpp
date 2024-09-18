#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <string>

#include "Commands.h"
#include "Functors.h"
#include "IOHelpers.h"
#include "Predicates.h"

namespace ivanov
{
    void area(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        StreamGuard guard(out);
        using namespace std::placeholders;
        std::string arg;
        in >> arg;
        std::function<double(double, const Polygon& rhs)> func;

        if (arg == "MEAN")
        {
            if (data.empty())
            {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
            func = std::bind(detail::accAreaMean, _1, _2, data.size());
        }
        else
        {
            predicate_t pred;
            if (arg == "ODD")
            {
                pred = hasOddVertexesCount;
            }
            else if (arg == "EVEN")
            {
                pred = hasEvenVertexesCount;
            }
            else
            {
                int size = std::stoul(arg);
                if (size < 3)
                {
                    throw std::invalid_argument("<INVALID COMMAND>");
                }
                pred = std::bind(checkVertexesCount, _1, size);
            }
            func = std::bind(detail::accAreaIf, _1, _2, pred);
        }
        out << std::fixed << std::setprecision(1);
        out << std::accumulate(data.cbegin(), data.cend(), 0.0, func);
    }

    void min(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        if (data.empty())
        {
            throw std::invalid_argument("INVALID COMMAND");
        }

        StreamGuard guard(out);
        std::string cmd;
        in >> cmd;
        if (cmd == "AREA")
        {
            out << std::fixed << std::setprecision(1);
            out << std::min_element(data.cbegin(), data.cend(), isLessArea)->computeArea();
        }
        else if (cmd == "VERTEXES")
        {
            out << std::min_element(data.cbegin(), data.cend(), isLessVertexesCount)->points.size();
        }
    }

    void max(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        if (data.empty())
        {
            throw std::invalid_argument("INVALID COMMAND");
        }

        StreamGuard guard(out);
        std::string cmd;
        in >> cmd;
        if (cmd == "AREA")
        {
            out << std::fixed << std::setprecision(1);
            out << std::max_element(data.cbegin(), data.cend(), isLessArea)->computeArea();
        }
        else if (cmd == "VERTEXES")
        {
            out << std::max_element(data.cbegin(), data.cend(), isLessVertexesCount)->points.size();
        }
    }

    void count(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        StreamGuard guard(out);
        using namespace std::placeholders;
        std::string arg;
        in >> arg;
        predicate_t pred;
        if (arg == "ODD")
        {
            pred = hasOddVertexesCount;
        }
        else if (arg == "EVEN")
        {
            pred = hasEvenVertexesCount;
        }
        else
        {
            int size = std::stoul(arg);
            if (size < 3)
            {
                throw std::invalid_argument("<INVALID COMMAND>");
            }
            pred = std::bind(checkVertexesCount, _1, size);
        }
        std::cout << std::count_if(data.cbegin(), data.cend(), pred);
    }

    void rmecho(std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        Polygon poly;
        in >> poly;
        if (data.empty())
        {
            throw std::invalid_argument("INVALID COMMAND");
        }
        std::size_t rmCnt = 0;
        auto removedIt = std::unique(data.begin(), data.end(), [&poly](const Polygon& left, const Polygon& right) {
            return (left == poly && right == poly);
            });
        rmCnt = std::distance(removedIt, data.end());
        data.erase(removedIt, data.end());
        out << rmCnt << '\n';
    }

    void same(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
    {
        StreamGuard guard(out);
        Polygon targetPolygon;
        in >> targetPolygon;

        if (in.fail())
        {
            throw std::invalid_argument("<INVALID COMMAND>");
        }

        auto countCompatible = std::count_if(data.cbegin(), data.cend(), [&targetPolygon](const Polygon& polygon) {
            return polygon.isCompatibleWith(targetPolygon);
            });

        out << countCompatible;
    }

    double detail::accAreaIf(double val, const Polygon& polygon, predicate_t pred)
    {
        return val + polygon.computeArea() * pred(polygon);
    }

    double detail::accAreaMean(double val, const Polygon& polygon, std::size_t size)
    {
        return val + polygon.computeArea() / size;
    }
}