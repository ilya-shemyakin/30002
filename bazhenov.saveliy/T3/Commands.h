#ifndef _COMMANDS_H
#define _COMMANDS_H
#include "Polygon.h"
#include <vector>

void area(const std::vector<Polygon>& vecPoly);
void min(const std::vector<Polygon>& vecPoly);
void max(const std::vector<Polygon>& vecPoly);
void count(const std::vector<Polygon>& vecPoly);
void echo(std::vector<Polygon>& vecPoly);
void rightShapes(const std::vector<Polygon>& vecPoly);

#endif
