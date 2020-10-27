#pragma once

#include <functional>
#include <iterator>
#include <tuple>
#include <concepts>

namespace algorithms {

/**
 * Quick sort method implementation class.
 *
 * Properties:
 *   - Not stable
 *   - Inplace
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: 2N * lnN
 *   - Best-case performance: N
 *
 * Remark: improves quicksort in presence of duplicates keys.
 */
class ThreeWayQuickSort {
public:
    template<typename It>
    using ValueType = typename std::iterator_traits<It>::value_type;

    template<std::random_access_iterator It>
    static void
    sort(It first, It last)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<std::random_access_iterator It, std::predicate<ValueType<It>, ValueType<It>> Compare>
    static void
    sort(It first, It last, Compare compare)
    {
        if (first >= last) {
            return;
        }

        sort(first, compare, 0, std::distance(first, last) - 1);
    }

private:
    template<typename It, typename Compare>
    static void
    sort(It input, Compare compare, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        auto [lt, gt] = partition(input, compare, lo, hi);
        if (lt > lo) {
            sort(input, compare, lo, lt - 1);
        }
        if (gt < hi) {
            sort(input, compare, gt + 1, hi);
        }
    }

    template<typename It, typename Compare>
    static std::tuple<std::size_t, std::size_t>
    partition(It input, Compare compare, std::size_t lo, std::size_t hi)
    {
        std::size_t lt = lo;
        std::size_t gt = hi;
        std::size_t i = lo;

        while (i <= gt) {
            int cmp = compareTo(input + i, input + lt, compare);
            if (cmp < 0) {
                std::swap(input[i++], input[lt++]);
            }
            else if (cmp > 0) {
                std::swap(input[i], input[gt--]);
            }
            else {
                i++;
            }
        }

        return std::make_tuple(lt, gt);
    }

    template<typename It, typename Compare>
    static int
    compareTo(It e1, It e2, Compare compare)
    {
        if (compare(*e1, *e2))
            return -1;
        if (compare(*e2, *e1))
            return +1;
        return 0;
    }
};

} // namespace algorithms
