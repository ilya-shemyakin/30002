#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <iostream>
#include <string>

#include <stdexcept>

#include "Edge.h"

using namespace std::string_literals;

class EdgeException : public std::logic_error {
public:
    EdgeException(const Edge& edge) :
        std::logic_error("Edge exception "s + std::to_string(edge.first) + " - " + std::to_string(edge.second)) {}
};

class MstException : public std::logic_error {
public:
    MstException(std::string s) : 
        std::logic_error(s) {}
};

#endif
