#ifndef POINT_HPP
#define POINT_HPP

namespace algorithms {

/**
 *
 */
struct Point {
    Point(double x, double y)
        : x{x}
        , y{y}
    { }

    double x;
    double y;
};

} // namespace algorithms

#endif // POINT_HPP
