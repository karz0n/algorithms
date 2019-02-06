#ifndef THREEWAYQUICK_HPP
#define THREEWAYQUICK_HPP

#include <iterator>
#include <functional>
#include <algorithm>
#include <tuple>

#include <Sequence.hpp>

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
 *
 * [quick-sort-3-way](https://www.toptal.com/developers/sorting-algorithms/quick-sort-3-way)
 */
class ThreeWayQuick {
public:
    template <typename RandomIt>
    static void sort(RandomIt first, RandomIt last)
    {
        using T = typename std::iterator_traits<RandomIt>::value_type;

        sort(first, last, std::less<T>{});
    }

    template <typename RandomIt, typename Less>
    static void sort(RandomIt first, RandomIt last, Less less)
    {
        if (first >= last) {
            return;
        }

        std::size_t size = std::distance(first, last);
        sort(first, less, 0, size - 1);
    }

private:
    template <typename RandomIt, typename Less>
    static void sort(RandomIt input, Less less, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        std::size_t lt = 0, gt = 0;
        std::tie(lt, gt) = partition(input, less, lo, hi);
        if (lt > lo) {
            sort(input, less, lo, lt - 1);
        }
        if (gt < hi) {
            sort(input, less, gt + 1, hi);
        }
    }

    template <typename RandomIt, typename Less>
    static std::tuple<std::size_t, std::size_t> partition(RandomIt input, Less less, std::size_t lo, std::size_t hi)
    {
        std::size_t lt = lo;
        std::size_t gt = hi;
        std::size_t i = lo;

        while (i <= gt) {
            int cmp = compareTo(input + i, input + lt, less);
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

    template <typename RandomIt, typename Less>
    static int compareTo(RandomIt e1, RandomIt e2, Less less)
    {
        if (less(*e1, *e2)) return -1;
        if (less(*e2, *e1)) return +1;
        return 0;
    }
};

} // namespace algorithm

#endif // THREEWAYQUICK_HPP
