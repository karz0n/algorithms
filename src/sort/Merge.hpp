#ifndef MERGE_HPP
#define MERGE_HPP

#include <vector>

#include "Sort.hpp"

namespace algorithms {

/**
 * Merge sort method implementation class.
 *
 * [merge-sort](https://www.toptal.com/developers/sorting-algorithms/merge-sort)
 */
class Merge : public Sort {
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
        std::vector<T> output(size);
        sort(first, output.begin(), less, 0, size - 1);
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
        sort(output, input, less, lo, mid);
        sort(output, input, less, mid + 1, hi);

        // merge two sorted parts
        merge(output, input, less, lo, mid, hi);
    }


    template <typename RandomIt, typename Less>
    static void merge(RandomIt left, RandomIt right, Less less, std::size_t lo, std::size_t mid, std::size_t hi)
    {
        std::size_t i = lo;
        std::size_t j = mid + 1;
        for (std::size_t k = lo; k <= hi; ++k) {
            if (i > mid) {
                right[k] = left[j++];
                continue;
            }
            if (j > hi) {
                right[k] = left[i++];
                continue;
            }
            if (less(left[j], left[i])) {
                right[k] = left[j++];
            }
            else {
                right[k] = left[i++];
            }
        }
    }
};

} // namespace algorithms

#endif // MERGE_HPP
