#ifndef SEGMENT_HPP
#define SEGMENT_HPP

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

    Point p1;
    Point p2;
};

/**
 * The set of segments.
 */
using Segments = std::vector<Segment>;

} // namespace algorithms

#endif // SEGMENT_HPP
