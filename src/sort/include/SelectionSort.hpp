#pragma once

#include <iterator>
#include <algorithm>
#include <functional>

namespace algorithms {

/**
 * Selection sort method implementation class.
 *
 * Properties:
 *   - Not stable
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: N^2 / 2
 *   - Best-case performance: N^2 / 2
 *
 * Remark: N exchanges.
 */
class SelectionSort {
public:
    template<std::forward_iterator It>
    static void
    sort(It first, It last)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<std::forward_iterator It,
             std::predicate<typename std::iterator_traits<It>::value_type,
                            typename std::iterator_traits<It>::value_type> Compare>
    static void
    sort(It first, It last, Compare compare)
    {
        if (first >= last) {
            return;
        }

        for (; first != last; ++first) {
            It min = first;
            for (auto it = std::next(first); it != last; ++it) {
                if (compare(*it, *min)) {
                    min = it;
                }
            }
            std::iter_swap(min, first);
        }
    }
};

} // namespace algorithms
