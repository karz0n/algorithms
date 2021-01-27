#pragma once

#include "Types.hpp"

namespace algorithms {

/**
 * Least-significant-digit-first string sort by key-indexed counting
 */
class LsdRadixSort {
public:
    static void
    sort(StringViews& views, std::size_t maxLength);

private:
    static void
    sort(StringViews& views, std::size_t maxLength, StringViews& aux);
};

} // namespace algorithms