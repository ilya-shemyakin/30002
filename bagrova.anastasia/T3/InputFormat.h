#ifndef INPUT_FORMAT_H
#define INPUT_FORMAT_H

#include "Point.h"
#include "Polygon.h"

#include <vector>

// Разделитель - символ
struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Point& point);
std::istream& operator>>(std::istream& in, Polygon& poly);
void load(std::string fileName, std::vector<Polygon>& data);
#endif
