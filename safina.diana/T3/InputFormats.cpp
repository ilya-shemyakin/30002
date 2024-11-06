#include "InputFormats.h"
#include "StreamGuard.h"

namespace shapes
{
    std::istream& operator>>(std::istream& in, DelimiterIO&& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        char c = '0';
        in >> c;
        if (in && (c != dest.exp))
        {
            in.unget();
            in.setstate(std::ios::failbit);
        }
        return in;
    }

    std::istream& operator>>(std::istream& in, Point& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        return in >> DelimiterIO{ '(' } >> dest.x >> DelimiterIO{ ';' } >>
            dest.y >> DelimiterIO{ ')' };
    }

    std::istream& operator>>(std::istream& in, Polygon& dest)
    {
        std::istream::sentry sentry(in);
        if (!sentry)
        {
            return in;
        }
        StreamGuard guard(in);

        Polygon inputPolygon;
        {
            in >> std::noskipws;

            int vertexesNumber = 0;
            in >> vertexesNumber;

            if (vertexesNumber < MIN_VERTEXES_NUMBER)
            {
                in.setstate(std::ios::failbit);
                return in;
            }

            Point point;
            for (int i = 0; i < vertexesNumber; ++i)
            {
                in >> DelimiterIO{ ' ' } >> point;
                inputPolygon.points.push_back(point);
            }
        }

        if (in.peek() != EOF)
        {
            in >> DelimiterIO{ '\n' };
        }

        if (in)
        {
            dest = inputPolygon;
        }
        return in;
    }
}
