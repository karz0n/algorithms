#ifndef QUICK_HPP
#define QUICK_HPP

#include <iostream>
#include <iterator>
#include <algorithm>

#include "Sort.hpp"
#include "Shuffle.hpp"

namespace algorithms {

/**
 * Quick sort method implementation class.
 *
 *
 */
class Quick : public Sort {
public:
    template <typename RandomIt>
    static void sort(RandomIt first, RandomIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<RandomIt>::value_type>{});
    }

    template <typename RandomIt, typename Less>
    static void sort(RandomIt first, RandomIt last, Less less)
    {
        if (first >= last) {
            return;
        }

        Shuffle::shuffle(first, last);
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

        std::size_t j = partition(input, less, lo, hi);
        if (j > lo) {
            sort(input, less, lo, j - 1);
        }
        if (j < hi) {
            sort(input, less, j + 1, hi);
        }
    }

    template <typename RandomIt, typename Less>
    static std::size_t partition(RandomIt input, Less less, std::size_t lo, std::size_t hi)
    {
        std::size_t i = lo;
        std::size_t j = hi + 1;
        while (true) {
            while (less(input[++i], input[lo])) {   //
                if (i == hi) break;                 //     Find item from left to right
            }                                       // (continue while input[i] < input[lo])

            while (less(input[lo], input[--j])) {   //
                if (j == lo) break;                 //     Find item from right to left
            }                                       // (continue while input[j] > input[lo])

            if (i >= j) break;                      // Quit when i and j crossed

            exchange(input + i, input + j);         // Exchange items to the right place
        }
        exchange(input + lo, input + j);
        return j;
    }
};

} // namespace algorithms

#endif // QUICK_HPP
