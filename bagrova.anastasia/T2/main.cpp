#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <iomanip>
#include <cctype>
#include <string>
#include <sstream>
#include <iterator>
#include <tuple>

struct DataStruct
{
    char key1;
    std::pair<long long, unsigned long long> key2;
    std::string key3;
};

bool operator==(const DataStruct& s1, const DataStruct& s2)
{
    return s1.key1 == s2.key1 && s1.key2 == s2.key2 && s1.key3 == s2.key3;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
    out << "(:key1 '" << data.key1 << '\'' <<
        ":key2 (:N " << data.key2.first << ":D " << data.key2.second << ":)" <<
        ":key3 \"" << data.key3 << "\":)";
    return out;
}

struct DelimiterIO
{
    char exp;
};

struct LabelIO
{
    std::string str;
};

struct ChrLitIO
{
    char c;
};

// num/den
struct RatLspIO
{
    long long num;
    unsigned long long den;
};

struct StrIO
{
    std::string& ref;
};

class StreamGuard
{
public:
    StreamGuard(std::istream& in):
        stream(in),
        flags(in.flags())
    {
        stream >> std::noskipws;
    }
    ~StreamGuard()
    {
        stream.flags(flags);
    }

private:
    std::istream& stream;
    std::basic_ios< char >::fmtflags flags;
};

std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    char c = '0';
    c = in.get();
    if (in && (c != dest.exp))
    {
        in.setstate(std::ios::failbit);
    }
    return in;
}

// "string"
std::istream& operator>>(std::istream& in, StrIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return std::getline(in >> DelimiterIO{ '"' }, dest.ref, '"');
}

//key
std::istream& operator>>(std::istream& in, LabelIO&& dest)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in; 
    }

    char c = '0';
    for (size_t i = 0; i < dest.str.size(); i++)
    {
        c = in.get();
        if (in && (c != dest.str[i]))
        {
            in.setstate(std::ios::failbit);
            break;
        }
    }
    return in;
}

// 'c'
std::istream& operator>>(std::istream& in, ChrLitIO& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }
    return in >> DelimiterIO{ '\'' } >> data.c >> DelimiterIO{ '\'' };
}

// (:N -1:D 5:)
std::istream& operator>>(std::istream& in, RatLspIO& data)
{
    std::istream::sentry sentry(in);
    if (!sentry)
    {
        return in;
    }

    in >> DelimiterIO{ '(' } >> DelimiterIO{ ':' } >>
        DelimiterIO{ 'N' } >> DelimiterIO{ ' ' };
    if (!in)
    {
        return in;
    }

    long long tempNum = 0;
    in >> tempNum;
    if (!in) 
    {
        return in;
    }
    in >> DelimiterIO{ ':' } >> DelimiterIO{ 'D' } >> DelimiterIO{ ' ' };

    std::string temp;
    getline(in, temp, ':');
    if (temp.size() == 0 || !isdigit(temp[0]))
    {
        in.setstate(std::ios::failbit);
        return in;
    }

    int i = 0;
    while (temp[i])
    {
        if (!isdigit(temp[i]))
        {
            in.setstate(std::ios::failbit);
            return in;
        }
        i += 1;
    }
    unsigned long long tempDen = 0;
    tempDen = stoll(temp);

    in >> DelimiterIO{ ')' };
    if (in)
    {
        data.num = tempNum;
        data.den = tempDen;
    }
    return in;
}

std::istream& readData(std::istream& in, DataStruct& rec) {
    StreamGuard guard(in);
    ChrLitIO symbol;
    RatLspIO rat;
    std::string str;

    in >> std::noskipws;
    in >> DelimiterIO{ '(' };

    for (int i = 0; i < 3; i++)
    {
        in >> DelimiterIO{ ':' } >> LabelIO{ "key" };
        char keyNumber = in.get();
        in >> DelimiterIO{ ' ' };

        if (keyNumber == '1')
        {
            in >> symbol;
        }
        else if (keyNumber == '2')
        {
            in >> rat;
        }
        else if (keyNumber == '3') 
        { 
            in >> StrIO{ str };
        }
        else
        {
            in.setstate(std::ios::failbit);
            return in;
        }
    }

    in >> DelimiterIO{ ':' } >> DelimiterIO{ ')' };
    if (in)
    {
        rec.key1 = symbol.c;
        rec.key2 = { rat.num, rat.den };
        rec.key3 = str;
    }
    return in;
}

std::istream& operator>>(std::istream& stream, DataStruct& rec)
{
    std::istream::sentry sentry(stream);
    if (!sentry)
    {
        return stream;
    }

    std::string line;
    while (getline(stream, line, '\n'))
    {
        std::istringstream in(line);
        DataStruct tempRec;
        if (readData(in, tempRec))
        {
            std::string tail;
            if (!getline(in, tail) || tail.empty())
            {
                rec = tempRec;
                break;
            }
        }
    }
    return stream;
}

bool test(const std::string& input, const std::vector<DataStruct>& v)
{
    std::vector<DataStruct> data;
    std::istringstream iss(input);

    std::copy(
        std::istream_iterator< DataStruct >(iss),
        std::istream_iterator< DataStruct >(),
        back_inserter(data)
    );
    return data == v;
}

int main()
{
    std::vector<DataStruct> data;
    std::istream_iterator<DataStruct> begCin(std::cin);

    std::copy(
        std::istream_iterator< DataStruct >(begCin),
        std::istream_iterator< DataStruct >(),
        back_inserter(data)
    );

    auto Comparator = [](const DataStruct& s1, const DataStruct& s2) {
        double rat1 = static_cast<double>(s1.key2.first) / s1.key2.second;
        double rat2 = static_cast<double>(s2.key2.first) / s2.key2.second;
        auto left = std::make_tuple(s1.key1, rat1, s1.key3.size());
        auto right = std::make_tuple(s2.key1, rat2, s2.key3.size());
        return left < right;
    };

    std::sort(data.begin(), data.end(), Comparator);

    std::copy(
        std::begin(data),
        std::end(data),
        std::ostream_iterator< DataStruct >(std::cout, "\n")
    );

    return 0;
}
