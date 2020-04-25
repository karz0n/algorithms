#pragma once

#include "Point.hpp"

namespace algorithms {

/**
 * The line segment.
 */
struct LineSegment {
    LineSegment() = default;

    LineSegment(const Point& p1, const Point& p2);

    bool
    isVertical() const;

    bool
    isHorizontal() const;

    bool
    isOrthogonal() const;

    bool
    operator<(const LineSegment& other) const;

    Point p1;
    Point p2;
};

} // namespace algorithms
