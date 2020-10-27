#pragma once

#include <functional>
#include <vector>
#include <concepts>

namespace algorithms {

/**
 * Merge sort method implementation class.
 *
 * Properties:
 *   - Stable
 *   - Worst-case performance: N * lgN
 *   - Average performance: N * lgN
 *   - Best-case performance: N * lgN
 */
class Merge {
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
        sort(first, buffer.begin(), compare, 0, size - 1);
    }

private:
    template<typename It, typename Compare>
    static void
    sort(It input, It output, Compare compare, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        // take middle of array
        std::size_t mid = lo + (hi - lo) / 2;

        // sort two parts
        sort(input, output, compare, lo, mid);
        sort(input, output, compare, mid + 1, hi);

        // merge two sorted parts
        merge(input, output, compare, lo, mid, hi);
    }

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
