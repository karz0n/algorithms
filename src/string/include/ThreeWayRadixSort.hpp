#pragma once

#include "Types.hpp"

namespace algorithms {

/**
 * Radix sort using three way partitioning.
 *
 * Properties:
 *   - Not stable
 *   - Inplace
 *   - Worst-case performance: 1.39 W N lgN
 *   - Average performance: 1.39 N lgN
 *   - Extra Space: logN + W
 */
class ThreeWayRadixSort {
public:
    static void
    sort(StringViews& views);

private:
    static void
    sort(StringViews& views, int lo, int hi, std::size_t d);
};

} // namespace algorithms