#include "commands.h"
using namespace std::placeholders;

void ivatshenko::area(const std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    std::string arg;
    std::getline(in, arg);
    arg.erase(0, 1);
    auto accumalateArea_if = [](double ac, const ivatshenko::Polygon& poly, int mod2, std::size_t vertices)
        {
            if ((poly.points.size() % 2 == mod2) || (mod2 == 2 && poly.points.size() == vertices) || (mod2 == 3))
            {
                ac += poly.getArea();
            }
            return ac;
        };
    if (arg == "EVEN")
    {
        out << std::accumulate(vector.begin(), vector.end(), 0.0,
            std::bind(accumalateArea_if, _1, _2, 0, 0)) << '\n';
    }
    else if (arg == "ODD")
    {
        out << std::accumulate(vector.begin(), vector.end(), 0.0,
            std::bind(accumalateArea_if, _1, _2, 1, 0)) << '\n';
    }
    else if (arg == "MEAN")
    {
        if (vector.size() == 0)
        {
            throw std::logic_error{ "<TOO FEW FIGURES>" };
        }
        out << std::accumulate(vector.begin(), vector.end(), 0.0,
            std::bind(accumalateArea_if, _1, _2, 3, 0)) / vector.size() << std::endl;
    }
    else if (isUnsignedInt(arg))
    {
        out << std::accumulate(vector.begin(), vector.end(), 0.0,
            std::bind(accumalateArea_if, _1, _2, 2, stoi(arg))) << '\n';
    }
    else
    {
        throw std::invalid_argument("<INVALID ARGUMENT>");
    }
}

void ivatshenko::max(const std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    std::string arg;
    std::getline(in, arg);
    arg.erase(0, 1);
    if (vector.empty())
    {
        throw std::logic_error{ "<TOO FEW FIGURES>" };
    }
    if (arg == "AREA")
    {
        out << std::max_element(
            vector.begin(),
            vector.end(),
            [](const Polygon& left, const Polygon& right)
            {
                return left.getArea() < right.getArea();
            }
        )->getArea() << '\n';
    }
    else if (arg == "VERTEXES")
    {
        out << std::accumulate(
            vector.begin() + 1,
            vector.end(),
            vector[0].points.size(),
            [](size_t max, const Polygon& poly)
            {
                return poly.points.size() > max ? poly.points.size() : max;
            }
        ) << '\n';
    }
    else
    {
        throw std::invalid_argument("<INVALID ARGUMENT>");
    }
}

void ivatshenko::min(const std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    std::string arg;
    std::getline(in, arg);
    arg.erase(0, 1);
    if (vector.empty())
    {
        throw std::logic_error{ "<TOO FEW FIGURES>" };
    }
    if (arg == "AREA")
    {
        out << std::min_element(
            vector.begin(),
            vector.end(),
            [](const Polygon& left, const Polygon& right)
            {
                return left.getArea() < right.getArea();
            }
        )->getArea() << '\n';
    }
    else if (arg == "VERTEXES")
    {
        out << std::accumulate(
            vector.begin() + 1,
            vector.end(),
            vector[0].points.size(),
            [](size_t min, const Polygon& poly)
            {
                return poly.points.size() < min ? poly.points.size() : min;
            }
        ) << '\n';
    }
    else
    {
        throw std::invalid_argument("<INVALID ARGUMENT>");
    }
}

void ivatshenko::count(const std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    std::string arg;
    std::getline(in, arg);
    arg.erase(0, 1);
    auto count_if = [](int ac, const Polygon& poly, int mod2, size_t vertexes)
        {
            if (poly.points.size() % 2 == mod2 || (mod2 == 2) && poly.points.size() == vertexes)
            {
                ac += 1;
            }
            return ac;
        };
    if (arg == "EVEN")
    {
        out << std::accumulate(
            vector.begin(),
            vector.end(),
            0,
            std::bind(count_if, _1, _2, 0, 0)
        ) << '\n';
    }
    else if (arg == "ODD")
    {
        out << std::accumulate(
            vector.begin(),
            vector.end(),
            0,
            std::bind(count_if, _1, _2, 1, 0)
        ) << '\n';
    }
    else if (isUnsignedInt(arg))
    {
        out << std::accumulate(
            vector.begin(),
            vector.end(),
            0,
            std::bind(count_if, _1, _2, 2, std::stoi(arg))
        ) << '\n';
    }
    else
    {
        throw std::invalid_argument{ "<INVALID ARGUMENT>" };
    }
}

void ivatshenko::inFrame(const std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    Polygon poly;
    in >> poly;
    if (in.fail() || in.get() != '\n')
        throw std::runtime_error("<INVALID ARGUMENT>");
    Frame frame = getFrame(vector);
    out << (frame.containsPolygon(poly) ? "<TRUE>" : "<FALSE>") << '\n';
}

void ivatshenko::rmecho(std::vector<ivatshenko::Polygon>& vector, std::istream& in, std::ostream& out)
{
    Polygon poly;
    in >> poly;
    if (in.fail() || in.get() != '\n')
    {
        throw std::invalid_argument{ "<INVALID ARGUMENT>" };
    }
    int rmCnt = 0;
    auto it = vector.begin(); 
    while (it != vector.end() - 1)
    {
        if (*it == *(it + 1) and *it == poly)
        {
            it = vector.erase(it);
            rmCnt += 1;
        }
        else {
            ++it;
        }
    }
    out << rmCnt << '\n';
}

bool ivatshenko::isUnsignedInt(const std::string& str)
{
    std::regex pattern("^[0-9]+$");
    return std::regex_match(str, pattern);
}
