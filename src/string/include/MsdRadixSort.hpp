#pragma once

#include "Types.hpp"

namespace algorithms {

class MsdRadixSort {
public:
    static void
    sort(StringViews& views);

private:
    static void
    sort(StringViews& views, StringViews& aux, long lo, long hi, std::size_t d);

    static void
    sort(StringViews& views, long lo, long hi);

    static unsigned char
    charAt(const std::string_view& view, std::size_t d);
};

} // namespace algorithms