#ifndef SELECT_HPP
#define SELECT_HPP

#include <iterator>
#include <algorithm>
#include <functional>

#include <Sequence.hpp>

namespace algorithms {

class Select {
public:
    template <typename T, typename RandomIt>
    static T get(RandomIt first, RandomIt last, std::size_t k)
    {
        return get<T>(first, last, std::less<T>{}, k);
    }

    template <typename T, typename RandomIt, typename Less>
    static T get(RandomIt first, RandomIt last, Less less, std::size_t k)
    {
        if (first >= last) {
            throw std::invalid_argument("Invalid iterator arguments");
        }

        std::size_t size = std::distance(first, last);
        if (k >= size) {
            throw std::logic_error("Invalid value of k argument");
        }

        Sequence::shuffle(first, last);

        std::size_t lo = 0, hi = size - 1;
        while (hi > lo) {
            std::size_t j = partition(first, less, lo, hi);
            if (j == k) {           // Target item has found
                return first[k];    //
            }
            if (k > j) {            // Target item on the right part
                lo = j + 1;         //
            }
            if (k < j) {            // Target item on the left part
                hi = j - 1;         //
            }
        }
        return first[k];
    }

private:
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

            std::iter_swap(input + i, input + j);   // Exchange items to the right place
        }
        std::iter_swap(input + lo, input + j);
        return j;
    }
};

} // namespace algorithms

#endif // SELECT_HPP
