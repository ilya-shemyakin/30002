#include <iostream>
#include <string>

#include <vector>
#include <set>

#include <algorithm>
#include <iterator>
#include <numeric>

#include "Point.h"
#include "Vec.h"
#include "Polygon.h"

#define EPS 1e-6

constexpr double determinant(double a, double b, double c, double d) {
    return a * d - b * c;
}

template <class T>
int sign(T value) {
    if (value > 0.0) {
        return 1;
    }
    if (value < 0.0) {
        return -1;
    }
    return 0;
}

constexpr bool between(double t, double a, double b) {
    return t > a - EPS && t < b + EPS;
}

bool checkIntersection(Point p1, Point p2, Point p3, Point p4) {
    double det = determinant(p2.x - p1.x, p3.x - p4.x, p2.y - p1.y, p3.y - p4.y);
    double det1 = determinant(p3.x - p1.x, p3.x - p4.x, p3.y - p1.y, p3.y - p4.y);
    double det2 = determinant(p2.x - p1.x, p3.x - p1.x, p2.y - p1.y, p3.y - p1.y);

    if (abs(det) < EPS) {
        if (abs(det1) < EPS && abs(det2) < EPS) {
            Vec v12(p1, p2), v13(p1, p3), v14(p1, p4), v34(p3, p4);
            double t12 = 1, t13 = v13/v12, t14 = v14/v12;
            double tmin = std::min(0.0, std::min(t13, t14));
            double tmax = std::max(1.0, std::max(t13, t14));
            double t34 = v34/v12;
            return abs(tmax - tmin) < abs(t12) + abs(t34) + EPS;
        }

        return false;
    }

    return between(det1 / det, 0, 1) && between(det2 / det, 0, 1);
}

std::vector<std::pair<int, int>> connectedVerteces(size_t n) {
    std::vector<std::pair<int, int>> v(n);
    int counter = -1;
    auto g = [&counter]() {
        ++counter;
        return std::pair<int, int>{counter, counter + 1};
    };
    generate(v.begin(), v.end(), g);
    v.back().second = 0;
    return v;
}

template <typename T>
std::vector<std::pair<T, T>> genPairs(const std::vector<T>& v1, const std::vector<T>& v2) {
    size_t n = v1.size();
    size_t m = v2.size();
    std::vector<std::pair<T, T>> v(n * m);
    int counter = -1;
    auto g = [&counter, n, m, &v1, &v2]() {
        ++counter;
        return std::pair<T, T>{v1.at(counter / m), v2.at(counter% m)};
        };
    std::generate(v.begin(), v.end(), g);
    return v;
}

std::ostream& operator<<(std::ostream& out, const Polygon& poly) {
    out << poly.points.size();
    copy(
        poly.points.begin(),
        poly.points.end(),
        std::ostream_iterator<Point>(out, " ")
    );
    return out;
}

double Polygon::area() const {
    auto v = connectedVerteces(points.size());

    auto op = [this](double init, const std::pair<int, int>& p) {
        return init + points[p.first].x * points[p.second].y - points[p.first].y * points[p.second].x;
    };
    return abs(std::accumulate(begin(v), end(v), 0.0, op)) / 2;
}

bool Polygon::hasMutualPoint(const Polygon& other) const {
    std::set<Point, PointsComparator> pointsThis{ points.begin(),points.end() };
    std::set<Point, PointsComparator> pointsOther{ other.points.begin(), other.points.end() };

    std::vector<Point> resIntersect;

    std::set_intersection(pointsThis.begin(), pointsThis.end(),
        pointsOther.begin(), pointsOther.end(),
        std::back_inserter(resIntersect),
        PointsComparator{}
    );

    return resIntersect.size() > 0;
}

bool Polygon::containsPoint(const Point& point) const {
    auto el = connectedVerteces(points.size());

    auto op = [el, this, point](double summ, const std::pair<int, int>& pair) {
        int x1 = points.at(pair.first).x - point.x;
        int y1 = points.at(pair.first).y - point.y;
        int x2 = points.at(pair.second).x - point.x;
        int y2 = points.at(pair.second).y - point.y;

        return summ + std::acos((x1 * x2 + y1 * y2) / sqrt((x1 * x1 + y1 * y1) * (x2 * x2 + y2 * y2)))
            * sign(determinant(x1, y1, x2, y2));
        };

    return !(accumulate(begin(el), end(el), 0.0, op) <= EPS);
}
bool Polygon::intersect(const Polygon& other) const {
    if (hasMutualPoint(other)) {
        return true;
    }
    if (any_of(points.begin(), points.end(), [&other](const Point& p) {
        return other.containsPoint(p);
        })) {
        return true;
    }
    if(any_of(other.points.begin(), other.points.end(), [this](const Point& p) {
        return this->containsPoint(p);
        })) {
        return true;
    }

    auto e1 = connectedVerteces(points.size());
    auto e2 = connectedVerteces(other.points.size());
    auto u = genPairs(e1, e2);

    auto op = [this, &other, &u](const std::pair<std::pair<int, int>, std::pair<int, int>>& pp) {
        const Point& p11 = points.at(pp.first.first);
        const Point& p12 = points.at(pp.first.second);
        const Point& p21 = other.points.at(pp.second.first);
        const Point& p22 = other.points.at(pp.second.second);

        return checkIntersection(p11, p12, p21, p22);
    };

    return std::any_of(u.begin(), u.end(), op);
}

