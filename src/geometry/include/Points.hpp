#pragma once

#include "Point.hpp"

#include <vector>

namespace algorithms {

/**
 * The set of points.
 */
using Points = std::vector<Point>;

/**
 * Get distance between two points.
 *
 * @param p1 - the point one
 * @param p2 - the point two
 *
 * @return The distance between points.
 */
float
getDistance(const Point& p1, const Point& p2);

/**
 * Finds orientation of an ordered triplet of points (this one and given two points).
 *
 * @param p1 - the point one
 * @param p2 - the point two
 * @param p3 - the point three
 *
 * @return  0 - Collinear
 *         -1 - Clockwise
 *         +1 - Counterclockwise
 */
int
getOrientation(const Point& p1, const Point& p2, const Point& p3);

/**
 * Compare two points by X coordinate
 */
struct CompareByX {
    bool
    operator()(const Point& p1, const Point& p2) const;
};

/**
 * Compare two points by Y coordinate
 */
struct CompareByY {
    bool
    operator()(const Point& p1, const Point& p2) const;
};

/**
 * Compare two points by X and Y coordinates
 */
struct CompareByXY {
    bool
    operator()(const Point& p1, const Point& p2) const;
};

/**
 * Compare two points by polar order towards base point
 */
class CompareByPolarOrder {
public:
    explicit CompareByPolarOrder(const Point& base);

    bool
    operator()(const Point& p1, const Point& p2) const;

private:
    Point _base;
};

} // namespace algorithms
