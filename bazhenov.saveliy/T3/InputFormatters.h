#ifndef INPUTFORMATTERS_H
#define INPUTFORMATTERS_H

#include <iostream>
#include <vector>
#include "Polygon.h"

struct DelimiterI {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterI&& dest);
void load(const std::string& fileName, std::vector<Polygon>& data);

#endif
