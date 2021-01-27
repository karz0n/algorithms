#include "ThreeWayRadixSort.hpp"

namespace algorithms {

static int
charAt(const std::string_view& view, std::size_t d)
{
    return (d < view.size()) ? view[d] : -1 /* Return special value for shorter string */;
}

void
ThreeWayRadixSort::sort(StringViews& views)
{
    sort(views, 0, static_cast<int>(views.size()) - 1, 0);
}

void
ThreeWayRadixSort::sort(StringViews& views, int lo, int hi, std::size_t d)
{
    if (hi <= lo) {
        return;
    }

    int lt = lo;
    int gt = hi;
    int cr = lo + 1;

    const auto v = charAt(views[lo], d);
    while (cr <= gt) {
        const auto t = charAt(views[cr], d);
        if (t < v) {
            views[cr++].swap(views[lt++]);
            continue;
        }
        if (t > v) {
            views[cr].swap(views[gt--]);
            continue;
        }
        cr++;
    }

    sort(views, lo, lt - 1, d);
    if (v >= 0 /* Skip special value case */) {
        sort(views, lt, gt, d + 1);
    }
    sort(views, gt + 1, hi, d);
}

} // namespace algorithms
