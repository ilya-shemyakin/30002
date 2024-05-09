#include "Commands.h"

#include <string>

#include <cmath>
#include <functional>
#include <numeric>
#include <algorithm>
#include <iterator>

void cmd::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > resultFuncForArea;
  if (option == "EVEN")
  {
    resultFuncForArea = [](const Polygon& polygon) -> double
      {
        return polygon.points.size() % 2 != 0 ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
      };
  }
  else if (option == "ODD")
  {
    resultFuncForArea = [](const Polygon& polygon) -> double
      {
        return polygon.points.size() % 2 == 0 ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
      };
  }
  else if (option == "MEAN")
  {
    if (polygons.size() == 0)
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
    resultFuncForArea = [&polygons](const Polygon& polygon) -> double
      {
        return cmd::subcmd::getPolygonArea(polygon) / polygons.size();
      };
  }
  else
  {
    size_t numVertexes;
    try
    {
      numVertexes = std::stoull(option);
      if (numVertexes < 3)
      {
        throw std::invalid_argument("");
      }
      resultFuncForArea = [&numVertexes](const Polygon& polygon) -> double
        {
          return polygon.points.size() == numVertexes ? cmd::subcmd::getPolygonArea(polygon) : 0.0;
        };
    }
    catch (const std::invalid_argument&)
    {
      std::cerr << "<INVALID COMMAND>";
    }
  }
  out << std::accumulate
  (
    polygons.begin(), polygons.end(), 0.0,
    [&resultFuncForArea](double sum, const Polygon& polygon) -> double
    {
      return sum + resultFuncForArea(polygon);
    }
  );
}

void cmd::min(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  if (option == "AREA")
  {
    out << cmd::subcmd::getMinPolygonArea(polygons);
  }
  else if (option == "VERTEXES")
  {
    out << cmd::subcmd::getMinPolygonVertexes(polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>";
  }
}

void cmd::max(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > resultFuncForMax;
  if (option == "AREA")
  {
    out << cmd::subcmd::getMaxPolygonArea(polygons);
  }
  else if (option == "VERTEXES")
  {
    out << cmd::subcmd::getMaxPolygonVertexes(polygons);
  }
  else
  {
    std::cerr << "<INVALID COMMAND>";
  }
}

void cmd::count(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< size_t(const Polygon&) > resultFuncForCount;
  if (option == "EVEN")
  {
    resultFuncForCount = [](const Polygon& polygon) -> size_t
      {
        size_t result = 0;
        if (polygon.points.size() % 2 != 0)
        {
          result = 1;
        }
        return result;
      };
  }
  else if (option == "ODD")
  {
    resultFuncForCount = [](const Polygon& polygon) -> size_t
      {
        size_t result = 0;
        if (polygon.points.size() % 2 == 0)
        {
          result = 1;
        }
        return result;
      };
  }
  else
  {
    size_t numVertexes;
    try
    {
      numVertexes = std::stoull(option);
      if (numVertexes < 3)
      {
        throw std::invalid_argument("");
      }
      resultFuncForCount = [&numVertexes](const Polygon& polygon) -> size_t
        {
          size_t result = 0;
          if (polygon.points.size() == numVertexes)
          {
            result = 1;
          }
          return result;
        };
    }
    catch (const std::invalid_argument&)
    {
      std::cerr << "<INVALID COMMAND>";
    }
  }
  out << std::accumulate
  (
    polygons.begin(), polygons.end(), 0,
    [&resultFuncForCount](double sum, const Polygon& polygon) -> double
    {
      return sum + resultFuncForCount(polygon);
    }
  );
}

void cmd::perms(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon;
  in >> polygon;
  if (in.fail() || in.peek() != '\n')
  {
    throw std::invalid_argument("");
  }
  std::function< bool(const Polygon&) > pred = std::bind(subcmd::isPerms , std::placeholders::_1, polygon);
  out << count_if(polygons.cbegin(), polygons.cend(), pred);
}

void cmd::rightShapes(const std::vector<Polygon>& polygons, std::istream& in, std::ostream& out)
{
  using namespace std::placeholders;
  out << std::count_if(polygons.cbegin(), polygons.cend(), std::bind(subcmd::isHasRightAngle, _1));
}

double cmd::subcmd::getTriangleArea(const Point& p1, const Point& p2, const Point& p3)
{
  return 0.5 * std::abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
}

double cmd::subcmd::getPolygonArea(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    return 0.0;
  }
  std::vector<double> triangleAreas(polygon.points.size() - 2);
  using namespace std::placeholders;
  std::transform
  (
    polygon.points.begin() + 2,
    polygon.points.end(),
    std::next(polygon.points.begin(), 1),
    triangleAreas.begin(),
    std::bind(&cmd::subcmd::getTriangleArea, polygon.points[0], _1, _2)
  );
  return std::accumulate(triangleAreas.begin(), triangleAreas.end(), 0.0);
}

double cmd::subcmd::getMaxPolygonArea(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  auto maxIt = std::max_element(polygons.begin(), polygons.end(),
    [](const Polygon& a, const Polygon& b) -> bool
    {
      return cmd::subcmd::getPolygonArea(a) < cmd::subcmd::getPolygonArea(b);
    });
  return cmd::subcmd::getPolygonArea(*maxIt);
}

double cmd::subcmd::getMinPolygonArea(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    return 0.0;
  }
  auto minIt = std::min_element(polygons.begin(), polygons.end(),
    [](const Polygon& a, const Polygon& b) -> bool
    {
      return cmd::subcmd::getPolygonArea(a) < cmd::subcmd::getPolygonArea(b);
    });
  return cmd::subcmd::getPolygonArea(*minIt);
}

size_t cmd::subcmd::getMaxPolygonVertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    return 0;
  }

  auto maxIt = std::max_element(polygons.begin(), polygons.end(),
    [](const Polygon& a, const Polygon& b) -> bool
    {
      return a.points.size() < b.points.size();
    });
  return maxIt->points.size();
}

size_t cmd::subcmd::getMinPolygonVertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty())
  {
    return 0;
  }
  auto minIt = std::min_element(polygons.begin(), polygons.end(),
    [](const Polygon& a, const Polygon& b) -> bool
    {
      return a.points.size() < b.points.size();
    });
  return minIt->points.size();
}

bool cmd::subcmd::isPointInPolygon(const Polygon& polygon, const Point& point)
{
  Point rotatePoint({ point.y, point.x });
  return std::find(polygon.points.begin(), polygon.points.end(), point) != polygon.points.cend() ||
    std::find(polygon.points.begin(), polygon.points.end(), rotatePoint) != polygon.points.cend();
}

bool cmd::subcmd::isPerms(const Polygon& pl1, const Polygon& pl2)
{
  if (pl1.points.size() != pl2.points.size())
  {
    return false;
  }
  using namespace std::placeholders;
  return std::distance(pl2.points.cbegin(), pl2.points.cend()) == 
    std::count_if(pl1.points.cbegin(), pl1.points.cend(), std::bind(isPointInPolygon, pl2, _1));
}

bool cmd::subcmd::isHasRightAngle(const Polygon& polygon)
{
  if (polygon.points.size() < 3)
  {
    throw std::invalid_argument("");
  }
  auto findRightAngle = RightAnglePred{ polygon.points[polygon.points.size() - 2], polygon.points[polygon.points.size() - 1] };
  return (std::find_if(polygon.points.cbegin(), polygon.points.cend(), findRightAngle) != polygon.points.cend());
}

bool cmd::subcmd::RightAnglePred::operator()(const Point& side2)
{
  Point vec1{ apex.x - point1.x, apex.y - point1.y };
  Point vec2{ apex.x - side2.x, apex.y - side2.y };
  point1 = apex;
  apex = side2;
  return ((vec1.x * vec2.x + vec1.y * vec2.y) == 0);
}
