#include <algorithm>
#include <functional>
#include <iomanip>
#include <numeric>
#include <string>

#include "Commands.h"
#include "Functors.h"
#include "IOHelpers.h"
#include "Predicates.h"

namespace maltsev
{
  void area(const std::vector< Polygon >& data, std::istream& in, std::ostream& out)
  {
    iofmtguard guard(out);
    using namespace std::placeholders;
    std::string arg;
    in >> arg;
    std::function< double(double, const Polygon& rhs) > func;
    
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
    out << arg << " ";
    out << std::fixed << std::setprecision(1);
    out << std::accumulate(data.cbegin(), data.cend(), 0.0, func);
  }

  void min(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
  {
    if (data.empty())
    {
      throw std::invalid_argument("INVALID COMMAND");
    }
    std::string cmd;
    in >> cmd;
    if (cmd == "AREA")
    {
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
    std::string cmd;
    in >> cmd;
    if (cmd == "AREA")
    {
      out << std::max_element(data.cbegin(), data.cend(), isLessArea)->computeArea();
    }
    else if (cmd == "VERTEXES")
    {
      out << std::max_element(data.cbegin(), data.cend(), isLessVertexesCount)->points.size();
    }
  }

  void count(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
  {
    iofmtguard guard(out);
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
    using namespace std::placeholders;
    Polygon polygon;
    in >> polygon;
    if (!in || in.peek() != '\n')
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }

    auto isEcho = [&polygon](const Polygon& lhs, const Polygon& rhs)
      { return lhs == polygon && rhs == polygon; };
    auto toRemoveIt = std::unique(data.begin(), data.end(),  isEcho);
    std::size_t removedCount = std::distance(toRemoveIt, data.end());
    data.erase(toRemoveIt, data.end());
    out << removedCount;
  }

  void intersections(const std::vector<Polygon>& data, std::istream& in, std::ostream& out)
  {
    if (data.empty())
    {
      throw std::logic_error("<INVALID COMMAND>");
    }

    Polygon polygon;
    in >> polygon;

    if (!in || in.peek() != '\n')
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    using namespace std::placeholders;
    auto intersectPredicate = std::bind(hasIntersection, std::cref(polygon), _1);
    out << std::count_if(data.cbegin(), data.cend(), intersectPredicate);
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
