#ifndef READER_H
#define READER_H

#include <iostream>

struct DelimiterI {
    char exp;
};


struct StringI {
    std::string& ref;
};

struct LabelI {
    const std::string& ref;
    bool ignoreCase = false;
};

struct LongLongI {
    unsigned long long& ref;
};

struct OctalLongLongI {
    unsigned long long& ref;
};

struct ExpectedCharI {
    const char& val;
    bool ignoreCase = false;
};

std::istream& operator>>(std::istream& in, DelimiterI&& dest);
std::istream& operator>>(std::istream& in, StringI&& dest);
std::istream& operator>>(std::istream& in, LabelI&& dest);
std::istream& operator>>(std::istream& in, LongLongI&& dest);
std::istream& operator>>(std::istream& in, OctalLongLongI&& dest);
std::istream& operator>>(std::istream& in, ExpectedCharI&& ExpChar);

#endif
