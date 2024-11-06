#ifndef FILL_VECTOR_H
#define FILL_VECTOR_H

#include <fstream>
#include <iterator>
#include <limits>
#include <exception>

#include "InputFormats.h"

namespace shapes
{
    std::vector< Polygon > fillVector(std::string fileName)
    {
        std::ifstream file(fileName);
        if (!file.is_open())
        {
            throw std::invalid_argument("Error! Unable to open the file called " + fileName +
                "\nCheck the spelling, the path and make sure that such a file exists\n");
        }

        std::vector< Polygon > shapes;

        while (!file.eof())
        {
            std::copy
            (
                std::istream_iterator< Polygon >(file),
                std::istream_iterator< Polygon >(),
                back_inserter(shapes)
            );

            if (file.fail())
            {
                bool eof = file.eof();
                file.clear();
                if (eof)
                {
                    file.setstate(std::ios::eofbit);
                }
                file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            }
        }

        file.close();
        return shapes;
    }
}

#endif
