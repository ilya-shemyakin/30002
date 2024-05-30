#ifndef IO_H
#define IO_H

#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include "figures.h"

namespace ivatshenko
{
  std::istream& operator>>(std::istream& in, ivatshenko::Point& poly);
  std::istream& operator>>(std::istream& in, ivatshenko::Polygon& poly);
  std::ostream& operator<<(std::ostream& out, const ivatshenko::Point& point);
  bool isPoint(std::string& str);
}
#endif
