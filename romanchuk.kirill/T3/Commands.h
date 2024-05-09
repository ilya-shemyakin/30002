#ifndef COMMANDS_H
#define COMMANDS_H

#include "Polygon.h"

namespace cmd //command
{
  void area(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void min(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void max(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void count(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);
  void perms(const std::vector< Polygon >& polygons, std::istream& in, std::ostream& out);

  namespace subcmd
  {
    double getTriangleArea(const Point& point1, const Point& point2, const Point& point3);
    double getPolygonArea(const Polygon& polygon);
    double getMaxPolygonArea(const std::vector< Polygon >& polygons);
    double getMinPolygonArea(const std::vector< Polygon >& polygons);
    size_t getMaxPolygonVertexes(const std::vector< Polygon >& polygons);
    size_t getMinPolygonVertexes(const std::vector< Polygon >& polygons);

    bool isPointInPolygon(const Polygon& polygon, const Point& point);
    bool isPerms(const Polygon& pl1, const Polygon& pl2);
  }
}

#endif // !COMMANDS_H
