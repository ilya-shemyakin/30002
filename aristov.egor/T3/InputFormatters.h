#ifndef INPUTFORMATTERS_H
#define INPUTFORMATTERS_H

#include<iostream>

struct Delimeter
{
  char exp;
};

std::istream& operator>>(std::istream& in, Delimeter&& dest);

#endif
