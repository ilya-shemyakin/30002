#include "commands.h"
using namespace std::placeholders;

void ivatshenko::area(const std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  auto accumalateArea_if =
    [](double ac, const ivatshenko::Polygon& poly, long unsigned int mod2, std::size_t vertices) {
      if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3))
      {
        ac += poly.getArea();
      }
      return ac;
    };
  if (arg == "EVEN")
  {
    out << std::accumulate(vector.begin(), vector.end(), 0.0, std::bind(accumalateArea_if, _1, _2, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    out << std::accumulate(vector.begin(), vector.end(), 0.0, std::bind(accumalateArea_if, _1, _2, 1, 0)) << '\n';
  }
  else if (arg == "MEAN")
  {
    if (vector.size() == 0)
    {
      throw std::invalid_argument{ "<INVALID COMMAND>" };
    }
    out << std::accumulate(vector.begin(), vector.end(), 0.0, std::bind(accumalateArea_if, _1, _2, 3, 0)) /
             vector.size()
        << std::endl;
  }
  else if (isUnsignedInt(arg))
  {
    if (std::stoi(arg) < 3)
    {
      throw std::invalid_argument{ "<INVALID COMMAND>" };
    };
    out << std::accumulate(vector.begin(), vector.end(), 0.0, std::bind(accumalateArea_if, _1, _2, 2, stoi(arg)))
        << '\n';
  }
  else
  {
    throw std::invalid_argument{ "<INVALID COMMAND>" };
  }
}

void ivatshenko::max(const std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  if (vector.empty())
  {
    throw std::invalid_argument{ "<INVALID COMMAND>" };
  }
  if (arg == "AREA")
  {
    out << std::max_element(
             vector.begin(), vector.end(),
             [](const Polygon& left, const Polygon& right) { return left.getArea() < right.getArea(); }
           )->getArea()
        << '\n';
  }
  else if (arg == "VERTEXES")
  {
    out << std::max_element(
             vector.begin(), vector.end(),
             [](const Polygon& left, const Polygon& right) { return left.points.size() < right.points.size(); }
           )->points.size()
        << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void ivatshenko::min(const std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  if (vector.empty())
  {
    throw std::logic_error{ "<INVALID COMMAND>" };
  }
  if (arg == "AREA")
  {
    out << std::min_element(
             vector.begin(), vector.end(),
             std::bind(std::less< double >{}, std::bind(&Polygon::getArea, _1), std::bind(&Polygon::getArea, _2))
           )
             ->getArea()
        << '\n';
  }
  /*if (arg == "AREA")
  {
    out << std::min_element(
             vector.begin(), vector.end(),
             [](const Polygon& left, const Polygon& right) { return left.getArea() < right.getArea(); }
           )->getArea()
        << '\n';
  }*/
  else if (arg == "VERTEXES")
  {
    out << std::min_element(
             vector.begin(), vector.end(),
             [](const Polygon& left, const Polygon& right) { return left.points.size() < right.points.size(); }
           )->points.size()
        << '\n';
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

void ivatshenko::count(const std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  std::string arg;
  in >> arg;
  auto count_if = [](int ac, const Polygon& poly, long unsigned int mod2, size_t vertexes) {
    if (poly.points.size() % 2 == mod2 || ((mod2 == 2) && poly.points.size() == vertexes))
    {
      ac += 1;
    }
    return ac;
  };
  if (arg == "EVEN")
  {
    out << std::accumulate(vector.begin(), vector.end(), 0, std::bind(count_if, _1, _2, 0, 0)) << '\n';
  }
  else if (arg == "ODD")
  {
    out << std::accumulate(vector.begin(), vector.end(), 0, std::bind(count_if, _1, _2, 1, 0)) << '\n';
  }
  else if (isUnsignedInt(arg))
  {
    if (std::stoi(arg) < 3)
    {
      throw std::invalid_argument{ "<INVALID COMMAND>" };
    };
    out << std::accumulate(vector.begin(), vector.end(), 0, std::bind(count_if, _1, _2, 2, std::stoi(arg))) << '\n';
  }
  else
  {
    throw std::invalid_argument{ "<INVALID COMMAND>" };
  }
}

void ivatshenko::inFrame(const std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  Polygon poly;
  in >> poly;
  if (in.fail() || in.get() != '\n')
  {
    throw std::invalid_argument{ "<INVALID COMMAND>" };
  }
  Frame frame = getFrame(vector);
  out << (frame.containsPolygon(poly) ? "<TRUE>" : "<FALSE>") << '\n';
}

void ivatshenko::rmecho(std::vector< ivatshenko::Polygon >& vector, std::istream& in, std::ostream& out)
{
  Polygon poly;
  in >> poly;
  if (in.fail() || in.get() != '\n')
  {
    throw std::invalid_argument{ "<INVALID COMMAND>" };
  }
  std::size_t rmCnt = 0;
  auto removedIt = std::unique(vector.begin(), vector.end(), [&poly](const Polygon& left, const Polygon& right) {
    return (left == poly && right == poly);
  });
  rmCnt = std::distance(removedIt, vector.end());
  vector.erase(removedIt, vector.end());
  out << rmCnt << '\n';
}

bool ivatshenko::isUnsignedInt(const std::string& str)
{
  std::regex pattern("^[0-9]+$");
  return std::regex_match(str, pattern);
}
