#pragma once

#include <iterator>
#include <concepts>
#include <utility>
#include <functional>

#include <Sequence.hpp>

namespace algorithms {

/**
 * Quick sort method implementation class.
 *
 * To get guaranteed complexity we shuffle given input.
 *
 * There is flaw in this method of sorting. If input array of elements
 * has a lot of equal keys, the time of sorting will be quadratic.
 *
 * Properties:
 *   - Not stable
 *   - Inplace
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: 2N * lnN
 *   - Best-case performance: N * lgN
 *
 * Remark: N * logN probabilistic guarantee fastest in practise.
 */
class QuickSort {
public:
    template<std::random_access_iterator It>
    static void
    sort(It first, It last, bool evadeWorstCase = true)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{}, evadeWorstCase);
    }

    template<std::random_access_iterator It,
             std::predicate<typename std::iterator_traits<It>::value_type,
                            typename std::iterator_traits<It>::value_type> Compare>
    static void
    sort(It first, It last, Compare compare, bool evadeWorstCase = true)
    {
        if (first >= last) {
            return;
        }

        // Shuffle input elements for case when they are ordered (worst case)
        if (evadeWorstCase) {
            Sequence::shuffle(first, last);
        }

        std::size_t size = std::distance(first, last);
        sort(first, compare, 0, size - 1);
    }

private:
    template<typename It, typename Compare>
    static void
    sort(It input, Compare compare, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        std::size_t j = partition(input, compare, lo, hi);
        if (j > lo) {
            sort(input, compare, lo, j - 1);
        }
        if (j < hi) {
            sort(input, compare, j + 1, hi);
        }
    }

    template<typename It, typename Compare>
    static std::size_t
    partition(It input, Compare compare, std::size_t lo, std::size_t hi)
    {
        std::size_t i = lo;
        std::size_t j = hi + 1;
        while (true) {
            // Find item from left to right greater than reference element
            while (compare(input[++i], input[lo])) {
                if (i == hi) {
                    break;
                }
            }

            // Find item from right to left less than reference element
            while (compare(input[lo], input[--j])) {
                if (j == lo) {
                    break;
                }
            }

            // Quit when i and j crossed
            if (i >= j) {
                break;
            }

            // Exchange items to the right place
            std::swap(input[i], input[j]);
        }
        // Place reference element to the right place (between two group of elements)
        std::swap(input[lo], input[j]);
        return j;
    }
};

} // namespace algorithms
