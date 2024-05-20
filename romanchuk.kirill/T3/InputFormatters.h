#ifndef INPUTFORMATTERS_H
#define INPUTFORMATTERS_H

#include <iostream>

struct DelimiterI
{
  char exp;
};

std::istream& operator>>(std::istream& in, DelimiterI&& dest);

#endif // !INPUTFORMATTERS_H
