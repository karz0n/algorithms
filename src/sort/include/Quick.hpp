#ifndef QUICK_HPP
#define QUICK_HPP

#include <iterator>
#include <algorithm>
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
class Quick {
public:
    template<typename RandomIt>
    static void sort(RandomIt first, RandomIt last)
    {
        using T = typename std::iterator_traits<RandomIt>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<typename RandomIt, typename Less>
    static void sort(RandomIt first, RandomIt last, Less less)
    {
        if (first >= last) {
            return;
        }

        // shuffle input elements for case when they are ordered (worst case)
        Sequence::shuffle(first, last);

        std::size_t size = std::distance(first, last);
        sort(first, less, 0, size - 1);
    }

private:
    template<typename RandomIt, typename Less>
    static void sort(RandomIt input, Less less, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        std::size_t j = partition(input, less, lo, hi);
        if (j > lo) {
            sort(input, less, lo, j - 1);
        }
        if (j < hi) {
            sort(input, less, j + 1, hi);
        }
    }

    template<typename RandomIt, typename Less>
    static std::size_t partition(RandomIt input, Less less, std::size_t lo, std::size_t hi)
    {
        std::size_t i = lo;
        std::size_t j = hi + 1;
        while (true) {
            //     Find item from left to right
            // (continue while input[i] < input[lo])
            while (less(input[++i], input[lo])) {
                if (i == hi) {
                    break;
                }
            }

            //     Find item from right to left
            // (continue while input[j] > input[lo])
            while (less(input[lo], input[--j])) { //

                if (j == lo) {
                    break;
                }
            }

            // Quit when i and j crossed
            if (i >= j) {
                break;
            }

            std::iter_swap(input + i, input + j); // Exchange items to the right place
        }
        std::iter_swap(input + lo, input + j);
        return j;
    }
};

} // namespace algorithms

#endif // QUICK_HPP
