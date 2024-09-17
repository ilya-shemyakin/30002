#ifndef READFROMFILE_H
#define READFROMFILE_H

#include<fstream>
#include<iterator>
#include<limits>
#include"Polygon.h"

void clean_istream(std::istream& in) {
  in.clear();
  in.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
}

std::vector< Polygon > read_polygons_from_file(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    throw std::runtime_error("ERROR, failed attempt to read a file");
  }
  std::vector< Polygon > arr;
  while (!file.eof()) {
    std::copy(
      std::istream_iterator< Polygon >{file}, std::istream_iterator< Polygon >{}, std::back_inserter(arr)
    );
    if (file.fail() && !file.eof()) {
      clean_istream(file);
    }
  }
  file.close();
  arr.shrink_to_fit();
  return arr;
}
#endif
