#ifndef MERGE_HPP
#define MERGE_HPP

#include <vector>
#include <functional>

namespace algorithms {

/**
 * Merge sort method implementation class.
 *
 * One optimization takes place. It swaps input/output in each recursion call.
 * It allows to us remoe copyng of elements in merge phase.
 * Underlying output is overlying input if we compare sort of higher order
 * and low order.
 *
 * Properties:
 *   + Stable
 *   + Worst-case performance: O(n log2 n)
 *   + Best-case performance: O(n log2 n)
 *   + Average performance: O(n log2 n)
 *
 * [merge-sort](https://www.toptal.com/developers/sorting-algorithms/merge-sort)
 */
class Merge {
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
        using T = typename std::iterator_traits<RandomIt>::value_type;

        if (first >= last) {
            return;
        }

        std::size_t size = std::distance(first, last);
        std::vector<T> buffer(size);
        sort(first, buffer.begin(), less, 0, size - 1);
    }

private:
    template <typename RandomIt, typename Less>
    static void sort(RandomIt input, RandomIt output, Less less, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        // take middle of array
        std::size_t mid = lo + (hi - lo) / 2;

        // sort two parts
        sort(output, input, less, lo, mid);         // Optimization with swapping of input/output
        sort(output, input, less, mid + 1, hi);     // Optimization with swapping of input/output

        // merge two sorted parts
        merge(output, input, less, lo, mid, hi);    // Optimization with swapping of input/output
    }

    template <typename RandomIt, typename Less>
    static void merge(RandomIt input, RandomIt output, Less less, std::size_t lo, std::size_t mid, std::size_t hi)
    {
        std::size_t i = lo;
        std::size_t j = mid + 1;
        for (std::size_t k = lo; k <= hi; ++k) {
            if (i > mid) {
                output[k] = input[j++];
            }
            else if (j > hi) {
                output[k] = input[i++];
            }
            else if (less(input[j], input[i])) {
                output[k] = input[j++];
            }
            else {
                output[k] = input[i++];
            }
        }
    }
};

} // namespace algorithms

#endif // MERGE_HPP
