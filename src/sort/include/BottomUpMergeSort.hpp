#pragma once

#include <functional>
#include <iterator>
#include <vector>
#include <concepts>

namespace algorithms {

/**
 * Bottom-up merge sort method implementation class.
 *
 * Bottom-up merge sort is modification of merge sort. It doesn't contain
 * recursion.
 *
 * Properties:
 *   - Stable
 *   - Worst-case performance: N * lgN
 *   - Best-case performance: N * lgN
 *   - Average performance: N * lgN
 */
class BottomUpMergeSort {
public:
    template<std::random_access_iterator It>
    static void
    sort(It first, It last)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<std::random_access_iterator It,
             std::predicate<typename std::iterator_traits<It>::value_type,
                            typename std::iterator_traits<It>::value_type> Compare>
    static void
    sort(It first, It last, Compare compare)
    {
        using T = typename std::iterator_traits<It>::value_type;

        if (first >= last) {
            return;
        }

        std::size_t size = std::distance(first, last);
        std::vector<T> buffer(size);
        for (std::size_t step = 1; step < size; step += step) {
            for (std::size_t lo = 0; lo < size - step; lo += 2 * step) {
                merge(first,
                      buffer.begin(),
                      compare,
                      lo,
                      lo + step - 1,
                      std::min(lo + 2 * step - 1, size - 1));
            }
        }
    }

private:
    template<typename It, typename Compare>
    static void
    merge(It to, It from, Compare compare, std::size_t lo, std::size_t mid, std::size_t hi)
    {
        // copy elements to buffer
        for (std::size_t k = lo; k <= hi; ++k) {
            from[k] = std::move(to[k]);
        }

        // merge two parts
        std::size_t i = lo;
        std::size_t j = mid + 1;
        for (std::size_t k = lo; k <= hi; ++k) {
            if (i > mid) {
                to[k] = std::move(from[j++]);
                continue;
            }
            if (j > hi) {
                to[k] = std::move(from[i++]);
                continue;
            }
            to[k] = compare(from[j], from[i]) ? std::move(from[j++]) : std::move(from[i++]);
        }
    }
};

} // namespace algorithms
