#include "Commands.h"
#include "StreamGuard.h"

#include<functional>
#include<cmath>
#include<algorithm>
#include<numeric>
#include<string>



void cmd::area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  StreamGuard guard(out);
  out << std::setprecision(1) << std::fixed;
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > res_function;
  if (option == "EVEN") {
    res_function = [](const Polygon& polygon) {
      return polygon.points_arr.size() % 2 == 0 ? cmd::subcmd::polygon_area(polygon) : 0.0;
      };
  }
  else if (option == "ODD") {
    res_function = [](const Polygon& polygon) {
      return polygon.points_arr.size() % 2 != 0 ? cmd::subcmd::polygon_area(polygon) : 0.0;
      };
  }
  else if (option == "MEAN") {
    if (polygons.empty()) {
      throw std::invalid_argument("for MEAN you need at least one figure");
    }
    res_function = [polygons](const Polygon& polygon) {
      return cmd::subcmd::polygon_area(polygon) / polygons.size(); //изначально здесь было [&vector]
      };
  }
  else {
    size_t vertices_count;
    try {
      vertices_count = std::stoull(option);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("ERROR: too many vertices");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("ERROR: command not found");
    }
    if (vertices_count < 3) {
      throw std::invalid_argument("ERROR: too few vertices");
    }
    res_function = [&vertices_count](const Polygon& polygon){
      return polygon.points_arr.size() == vertices_count ? cmd::subcmd::polygon_area(polygon) : 0.0;
      };
  }
  out << std::accumulate(
    polygons.begin(), polygons.end(), 0.0,
    [&res_function](double sum, const Polygon& polygon) { return sum + res_function(polygon); }
  ) << std::endl;
}

void cmd::max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > res_function;
  if (option == "AREA") {
    StreamGuard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << cmd::subcmd::max_area(polygons) << std::endl;
  }
  else if (option == "VERTEXES") {
    out << cmd::subcmd::max_vertexes(polygons) << std::endl;
  }
  else {
    throw std::invalid_argument("ERROR: command not found");
  }
}

void cmd::min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< double(const Polygon&) > res_function;
  if (option == "AREA") {
    StreamGuard guard(out);
    out << std::setprecision(1) << std::fixed;
    out << cmd::subcmd::min_area(polygons) << std::endl;
  }
  else if (option == "VERTEXES") {
    out << cmd::subcmd::min_vertexes(polygons) << std::endl;
  }
  else {
    throw std::invalid_argument("ERROR: command not found");
  }
}

void cmd::count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  std::string option;
  in >> option;
  std::function< size_t(const Polygon&) > res_function;
  if (option == "EVEN") {
    res_function = [](const Polygon& polygon) {return (polygon.points_arr.size() % 2 == 0) ? 1 : 0; };
  }
  else if (option == "ODD") {
    res_function = [](const Polygon& polygon) {return (polygon.points_arr.size() % 2 != 0) ? 1 : 0; };
  }
  else {
    size_t vert_count;
    try {
      vert_count = std::stoull(option);
    }
    catch (const std::out_of_range&) {
      throw std::invalid_argument("ERROR: too many vertices");
    }
    catch (const std::exception&) {
      throw std::invalid_argument("ERROR: command not found");
    }
    if (vert_count < 3) {
      throw std::invalid_argument("ERROR: too few vertices");
    }
    res_function = [&vert_count](const Polygon& polygon) {
      return (polygon.points_arr.size() == vert_count) ? 1 : 0;
      };
  }
  out << std::accumulate(
    polygons.begin(), polygons.end(), 0,
    [&res_function](double summ, const Polygon& polygon) {
      return summ + res_function(polygon);
    }
  ) << std::endl;
}

void cmd::lessarea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon_in;
  in >> polygon_in;
  if (in.fail() || in.peek() != '\n') {
    throw std::invalid_argument("ERROR: could not read the figure");
  }
  out << std::accumulate(
    polygons.begin(), polygons.end(), 0,
    [polygon_in](double summ, const Polygon& polygon) {
      return summ + ((cmd::subcmd::polygon_area(polygon) < cmd::subcmd::polygon_area(polygon_in)) ? 1 : 0);
    }
  ) << std::endl;
}

void cmd::maxseq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out)
{
  Polygon polygon_in;
  in >> polygon_in;
  if (in.fail() || in.peek() != '\n') {
    throw std::invalid_argument("ERROR: could not read the figure");
  }
  std::vector<int> seq;
  int count = 0;
  std::transform(
    polygons.begin(), polygons.end(), std::back_inserter(seq),
    [&count, &polygon_in](const Polygon& polygon) {
      if (polygon == polygon_in) {
        count++;
      }
      else {
        count = 0;
      }
      return count;
    }
  );
  seq.push_back(0);
  out << *std::max_element(seq.begin(), seq.end()) << std::endl;
}

double cmd::subcmd::polygon_area(const Polygon& polygon)
{
  if (polygon.points_arr.size() < 3) {
    return 0.0;
  }
  std::vector< double > triangle_areas(polygon.points_arr.size() - 2);
  using namespace std::placeholders;
  std::transform(
    polygon.points_arr.begin() + 2, polygon.points_arr.end(), std::next(polygon.points_arr.begin(), 1), triangle_areas.begin(),
    std::bind(&cmd::subcmd::triangle_area, polygon.points_arr[0], _1, _2)
  );
  return std::accumulate(triangle_areas.begin(), triangle_areas.end(), 0.0);
}

double cmd::subcmd::triangle_area(const Point& p1, const Point& p2, const Point& p3)
{
  return 0.5 * std::abs((p1.x - p3.x) * (p2.y - p1.y) - (p1.x - p2.x) * (p3.y - p1.y));
}

double cmd::subcmd::max_area(const std::vector< Polygon >& polygons)
{
  if (polygons.empty()) {
    throw std::invalid_argument("ERROR: need at least one figure");
  }
  return cmd::subcmd::polygon_area(*std::max_element(
    polygons.begin(), polygons.end(),
    [](const Polygon& left, const Polygon& right) {
      return cmd::subcmd::polygon_area(left) < cmd::subcmd::polygon_area(right);
    }
  ));
}

size_t cmd::subcmd::max_vertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty()) {
    throw std::invalid_argument("ERROR: need at least one figure");
  }
  using namespace std::placeholders;
  return std::max_element(
    polygons.begin(), polygons.end(),
    [](const Polygon& left, const Polygon& right) {
      return left.points_arr.size() < right.points_arr.size();
    }
  )->points_arr.size();
}

double cmd::subcmd::min_area(const std::vector< Polygon >& polygons)
{
  if (polygons.empty()) {
    throw std::invalid_argument("ERROR: need at least one figure");
  }
  return cmd::subcmd::polygon_area(*std::max_element(
    polygons.begin(), polygons.end(),
    [](const Polygon& left, const Polygon& right) {
      return cmd::subcmd::polygon_area(left) > cmd::subcmd::polygon_area(right);
    }
  ));
}

size_t cmd::subcmd::min_vertexes(const std::vector< Polygon >& polygons)
{
  if (polygons.empty()) {
    throw std::invalid_argument("ERROR: need at least one figure");
  }
  using namespace std::placeholders;
  return std::max_element(
    polygons.begin(), polygons.end(),
    [](const Polygon& left, const Polygon& right) {
      return left.points_arr.size() > right.points_arr.size();
    }
  )->points_arr.size();
}
