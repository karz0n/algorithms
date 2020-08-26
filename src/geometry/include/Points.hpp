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
 * @return 0 - Collinear
 *         1 - ClockWise
 *         2 - CounterClockWise
 */
int
getOrientation(const Point& p1, const Point& p2, const Point& p3);

} // namespace algorithms
