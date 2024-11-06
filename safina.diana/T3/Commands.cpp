#include <algorithm>
#include <numeric>
#include <string>

#include "Commands.h"
#include "InputFormats.h"
#include "StreamGuard.h"

namespace cmd
{
    void area(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        std::string option = "";
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Incorrect option is givan\n");
        }

        if (option == "EVEN")
        {
            out << std::accumulate(shapes.cbegin(), shapes.cend(), 0.0,
                [](double areaSum, const shapes::Polygon& shape)
                {
                    if (shape.points.size() % 2 == 0)
                    {
                        return areaSum + getShapeArea(shape);
                    }
                    return areaSum;
                }
            );
        }
        else if (option == "ODD")
        {
            out << std::accumulate(shapes.cbegin(), shapes.cend(), 0.0,
                [](double areaSum, const shapes::Polygon& shape)
                {
                    if (shape.points.size() % 2)
                    {
                        return areaSum + getShapeArea(shape);
                    }
                    return areaSum;
                }
            );
        }
        else if (option == "MEAN")
        {
            if (shapes.empty())
            {
                throw std::invalid_argument("At least 1 shape is required to "
                    "calculate mean area\n");
            }

            out << std::accumulate(shapes.cbegin(), shapes.cend(), 0.0,
                [](double areaSum, const shapes::Polygon& shape)
                {
                    return areaSum + getShapeArea(shape);
                }
            ) / shapes.size();
        }
        else
        {
            long unsigned int verticesNum = std::stoi(option);
            if (verticesNum < shapes::MIN_VERTEXES_NUMBER)
            {
                throw std::invalid_argument("Error! A polygon has 3 vertices minimum\n");
            }

            out << std::accumulate(shapes.cbegin(), shapes.cend(), 0.0,
                [&verticesNum](double areaSum, const shapes::Polygon& shape)
                {
                    if (shape.points.size() == verticesNum)
                    {
                        return areaSum + getShapeArea(shape);
                    }
                    return areaSum;
                }
            );
        }
    }

    void max(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        std::string option = "";
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Incorrect option is givan\n");
        }

        if (shapes.empty())
        {
            throw std::invalid_argument("At least 1 shape is required to calculate max values\n");
        }

        if (option == "AREA")
        {
            out << getShapeArea(*std::max_element(shapes.cbegin(), shapes.cend(),
                [](const shapes::Polygon& shape1, const shapes::Polygon& shape2)
                {
                    return getShapeArea(shape1) < getShapeArea(shape2);
                }
            ));
        }
        else if (option == "VERTEXES")
        {
            out << (*std::max_element(shapes.cbegin(), shapes.cend(),
                [](const shapes::Polygon& shape1, const shapes::Polygon& shape2)
                {
                    return shape1.points.size() < shape2.points.size();
                }
            )).points.size();
        }
        else
        {
            throw std::invalid_argument("Error! There is no such option\n");
        }
    }

    void min(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        std::string option = "";
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Incorrect option is givan\n");
        }

        if (shapes.empty())
        {
            throw std::invalid_argument("At least 1 shape is required to calculate min values\n");
        }

        if (option == "AREA")
        {
            out << getShapeArea(*std::min_element(shapes.begin(), shapes.end(),
                [](const shapes::Polygon& shape1, const shapes::Polygon& shape2)
                {
                    return getShapeArea(shape1) < getShapeArea(shape2);
                }
            ));
        }
        else if (option == "VERTEXES")
        {
            out << (*std::min_element(shapes.begin(), shapes.end(),
                [](const shapes::Polygon& shape1, const shapes::Polygon& shape2)
                {
                    return shape1.points.size() < shape2.points.size();
                }
            )).points.size();
        }
        else
        {
            throw std::invalid_argument("Error! There is no such option\n");
        }
    }

    void count(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        std::string option = "";
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Incorrect option is givan\n");
        }

        if (option == "EVEN")
        {
            out << std::count_if(shapes.cbegin(), shapes.cend(),
                [](const shapes::Polygon& shape)
                {
                    return shape.points.size() % 2 == 0;
                }
            );
        }
        else if (option == "ODD")
        {
            out << std::count_if(shapes.cbegin(), shapes.cend(),
                [](const shapes::Polygon& shape)
                {
                    return shape.points.size() % 2;
                }
            );
        }
        else
        {
            long unsigned int verticesNum = std::stoi(option);
            if (verticesNum < shapes::MIN_VERTEXES_NUMBER)
            {
                throw std::invalid_argument("Error! A polygon has 3 vertices minimum\n");
            }

            out << std::count_if(shapes.cbegin(), shapes.cend(),
                [&verticesNum](const shapes::Polygon& shape)
                {
                    return shape.points.size() == verticesNum;
                }
            );
        }
    }

    void perms(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        shapes::Polygon option;
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Error! Incorrect polygon is given\n");
        }

        out << std::count_if(shapes.cbegin(), shapes.cend(),
            [&option](const shapes::Polygon& shape)
            {
                return std::is_permutation(shape.points.cbegin(), shape.points.cend(),
                option.points.cbegin(), option.points.cend());

            }
        );
    }

    void maxseq(const std::vector< shapes::Polygon >& shapes, std::istream& in, std::ostream& out)
    {
        shapes::StreamGuard guard(in);
        in >> std::noskipws;

        shapes::Polygon option;
        in >> shapes::DelimiterIO{ ' ' } >> option;

        if (in.fail())
        {
            throw std::invalid_argument("Error! Incorrect polygon is given\n");
        }

        std::vector<int> sequences;
        int count = 0;
        std::transform(shapes.cbegin(), shapes.cend(), back_inserter(sequences),
            [&count, &option](const shapes::Polygon& shape)
            {
                if (shape == option)
                {
                    count++;
                }
                else
                {
                    count = 0;
                }
                return count;
            }
        );
        sequences.push_back(0);
        out << *std::max_element(sequences.cbegin(), sequences.cend());
    }

    double getShapeArea(const shapes::Polygon& shape)
    {
        std::vector< std::pair< int, int > > pairs = generatePairIndexes(shape.points.size());
        return 0.5 * std::abs(std::accumulate(pairs.cbegin(), pairs.cend(), 0,
            [&shape](double areaSum, std::pair< int, int > ind)
            {
                return areaSum + shape.points[ind.first].x *
                    shape.points[ind.second % shape.points.size()].y -
                    shape.points[ind.second % shape.points.size()].x * shape.points[ind.first].y;
            }
        ));
    }

    std::vector< std::pair< int, int > > generatePairIndexes(size_t shapeSize)
    {
        std::vector< std::pair< int, int > > res(shapeSize);
        int count = -1;
        std::generate(res.begin(), res.end(),
            [&count]()
            {
                count++;
                return std::pair< int, int >{count, count + 1};
            }
        );
        return res;
    }
}
