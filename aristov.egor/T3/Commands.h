#ifndef COMMANDS_H
#define COMMANDS_H

#include"Polygon.h"
#include"Point.h"

namespace cmd
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void lessarea(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void maxseq(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  namespace subcmd
  {
    double polygon_area(const Polygon& polygon);
    double triangle_area(const Point& p1, const Point& p2, const Point& p3);
    double max_area(const std::vector< Polygon >& polygons);
    size_t max_vertexes(const std::vector< Polygon >& polygons);
    double min_area(const std::vector< Polygon >& polygons);
    size_t min_vertexes(const std::vector< Polygon >& polygons);
  }
}

#endif
