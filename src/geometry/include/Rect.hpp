#pragma once

#include "Point.hpp"

namespace algorithms {

struct Rect {
    Rect(const Point& topLeft, const Point& bottomRight);

    Rect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

    bool
    operator==(const Rect& other) const;
    bool
    operator!=(const Rect& other) const;

    bool
    isOrthogonal() const;

    Point p1; //!> Top Left
    Point p2; //!> Bottom Left
    Point p3; //!> Top Right
    Point p4; //!> Bottom Right
};

} // namespace algorithms
