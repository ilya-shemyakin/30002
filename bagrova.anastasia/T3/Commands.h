#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>

#include "Polygon.h"

bool convertToSize(const std::string& str, int& value);
bool process(const std::string& cmd, std::vector<Polygon>& data);

#endif
