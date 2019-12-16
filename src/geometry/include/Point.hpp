#pragma once

#include <cmath>
#include <limits>
#include <vector>

namespace algorithms {

struct Point {
    constexpr Point()
        : x{0.0}
        , y{0.0}
    {
    }

    constexpr Point(double x, double y)
        : x{x}
        , y{y}
    {
    }

    constexpr bool operator==(const Point& other) const
    {
        return equalByX(other) && equalByX(other);
    }

    constexpr bool equalByX(const Point& other) const
    {
        return std::abs(x - other.x) < std::numeric_limits<double>::epsilon();
    }

    constexpr bool equalByY(const Point& other) const
    {
        return std::abs(y - other.y) < std::numeric_limits<double>::epsilon();
    }

    /**
     * Finds orientation given segment and this point.
     *
     * @param p - the point one
     * @param q - the point two
     *
     * @return 0 - Colinear
     *         1 - ClockWise
     *         2 - CounterClockWise
     */
    constexpr int orientTo(const Point& p, const Point& q) const
    {
        double v = (q.y - p.y) * (x - q.x) - (q.x - p.x) * (y - q.y);
        return (v == 0.0) ? 0 : (v > 0.0) ? 1 : 2;
    }

    double x;
    double y;
};

/**
 * The set of points.
 */
using Points = std::vector<Point>;

} // namespace algorithms
