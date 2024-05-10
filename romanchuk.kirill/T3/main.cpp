#include <iostream>
#include <functional>
#include <map>

#include "ReadPolygonsFromFile.h"
#include "Commands.h"

namespace mapCommands
{
  using mapCmd = std::map< std::string, std::function< void(std::istream&, std::ostream&) > >;
  mapCmd createMapOfCommands(std::vector< Polygon >& polygons, std::istream&, std::ostream&)
  {
    mapCmd commands;
    using namespace std::placeholders;
    commands["AREA"] = std::bind(cmd::area, std::cref(polygons), _1, _2);
    commands["MAX"] = std::bind(cmd::max, std::cref(polygons), _1, _2);
    commands["MIN"] = std::bind(cmd::min, std::cref(polygons), _1, _2);
    commands["COUNT"] = std::bind(cmd::count, std::cref(polygons), _1, _2);
    commands["PERMS"] = std::bind(cmd::perms, std::cref(polygons), _1, _2);
    commands["RIGHTSHAPES"] = std::bind(cmd::rightShapes, std::cref(polygons), _1, _2);
    return commands;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }
  std::vector< Polygon > polygons = readPolygonsFromFile(argv[1]);

  std::copy(polygons.begin(), polygons.end(), std::ostream_iterator<Polygon>(std::cout, "\n"));

  std::string argument;

  std::map< std::string, std::function< void(std::istream&, std::ostream&) > > commands;
  commands = mapCommands::createMapOfCommands(polygons, std::cin, std::cout);

  while (std::cin >> argument)
  {
    if (std::cin.eof())
    {
      break;
    }
    try
    {
      commands.at(argument)(std::cin, std::cout);
      std::cout << '\n';
    }
    catch (const std::out_of_range&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      cleanIStream(std::cin);
    }
    catch (const std::invalid_argument&)
    {
      std::cerr << "<INVALID COMMAND>\n";
      cleanIStream(std::cin);
    }
  }

  return 0;
}
