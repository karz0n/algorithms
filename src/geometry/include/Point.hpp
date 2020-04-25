#pragma once

namespace algorithms {

struct Point {
    Point();

    Point(float x, float y);

    bool
    operator==(const Point& other) const;

    bool
    operator!=(const Point& other) const;

    bool
    equalByX(const Point& other) const;

    bool
    equalByY(const Point& other) const;

    float x;
    float y;
};

} // namespace algorithms
