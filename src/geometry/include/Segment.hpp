#pragma once

#include <vector>

#include "Point.hpp"

namespace algorithms {

/**
 * The line segment.
 */
struct Segment {
    constexpr Segment(const Point& p1, const Point& p2)
        : p1{p1}
        , p2{p2}
    {
    }

    constexpr bool isVertical() const
    {
        return p1.equalByX(p2);
    }

    constexpr bool isHorizontal() const
    {
        return p1.equalByY(p2);
    }

    constexpr bool operator<(const Segment& other) const
    {
        if (p1.y < other.p1.y || p2.y < other.p2.y) {
            return true;
        }
        if (p1.y > other.p1.y || p2.y > other.p2.y) {
            return false;
        }
        if (p1.x < other.p1.x || p2.x < other.p2.x) {
            return true;
        }
        if (p1.x > other.p1.x || p2.x > other.p2.x) {
            return false;
        }
        return false;
    }

    Point p1;
    Point p2;
};

/**
 * The set of segments.
 */
using Segments = std::vector<Segment>;

} // namespace algorithms
