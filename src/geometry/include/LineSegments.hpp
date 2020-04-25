#pragma once

#include "LineSegment.hpp"

#include <vector>

namespace algorithms {

/**
 * The set of line segments.
 */
using LineSegments = std::vector<LineSegment>;

/**
 * Checks if one line segment intersects another.
 *
 * @param s1 - the segment one
 * @param s2 - the segment two
 *
 * @return \c true if s1 intersects s2, \c false otherwise
 */
bool
intersects(const LineSegment& s1, const LineSegment& s2);

} // namespace algorithms
