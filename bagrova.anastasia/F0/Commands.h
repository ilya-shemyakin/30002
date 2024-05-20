#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>

#include "Graph.h"

void invalidCommandMessage();
bool convertToSize(const std::string& str, int& value);
bool process(const std::string& cmd_string, Graph& data);

#endif
