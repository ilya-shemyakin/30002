#ifndef INPUT_FORMAT_H
#define INPUT_FORMAT_H

#include "Edge.h"

// Разделитель - символ
struct DelimiterIO {
    char exp;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest);
std::istream& operator>>(std::istream& in, Edge& edge);

#endif
