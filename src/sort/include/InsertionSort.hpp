#pragma once

#include <iterator>
#include <concepts>
#include <algorithm>
#include <functional>

namespace algorithms {

/**
 * Insertion sort method implementation class.
 *
 * Properties:
 *   - Stable
 *   - Inplace
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: N^2 / 4
 *   - Best-case performance: N
 *
 * Remark: Use for small N or partially ordered.
 */
class InsertionSort {
public:
    template<std::bidirectional_iterator It>
    static void
    sort(It first, It last)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<std::bidirectional_iterator It,
             std::predicate<typename std::iterator_traits<It>::value_type,
                            typename std::iterator_traits<It>::value_type> Compare>
    static void
    sort(It first, It last, Compare compare)
    {
        if (first >= last) {
            return;
        }

        for (auto it = std::next(first); it != last; ++it) {
            for (auto c = it; c != first;) {
                auto p = std::prev(c);
                if (compare(*c, *p)) {
                    std::iter_swap(c, p);
                    c = p;
                }
                else {
                    break;
                }
            }
        }
    }
};

} // namespace algorithms
