#ifndef BOTTOMUPMERGE_HPP
#define BOTTOMUPMERGE_HPP

#include <vector>
#include <algorithm>

#include "Sort.hpp"

namespace algorithms {

/**
 * Bottom-up merge sort method implementation class.
 *
 * Bottom-up merge sort is modification of merge sort. It doesn't contain
 * recursion.
 *
 * Properties:
 *   + Stable
 *   + Worst-case performance: O(n log2 n)
 *   + Best-case performance: O(n log2 n)
 *   + Average performance: O(n log2 n)
 */
class BottomUpMerge : public Sort {
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

        std::size_t N = std::distance(first, last);
        std::vector<T> buffer(N);
        for (std::size_t sz = 1; sz < N; sz += sz) {
            for (std::size_t lo = 0; lo < N - sz; lo += 2 * sz) {
                merge(first, buffer.begin(), less, lo, lo + sz - 1, std::min(lo + 2 * sz - 1, N - 1));
            }
        }
    }

private:
    template <typename RandomIt, typename Less>
    static void merge(RandomIt input, RandomIt output, Less less, std::size_t lo, std::size_t mid, std::size_t hi)
    {
        for (std::size_t k = lo; k <= hi; ++k) {
            output[k] = input[k];
        }

        std::size_t i = lo;
        std::size_t j = mid + 1;
        for (std::size_t k = lo; k <= hi; ++k) {
            if (i > mid) {
                input[k] = output[j++];
            }
            else if (j > hi) {
                input[k] = output[i++];
            }
            else if (less(output[j], output[i])) {
                input[k] = output[j++];
            }
            else {
                input[k] = output[i++];
            }
        }
    }
};

} // namespace algorithms

#endif // BOTTOMUPMERGE_HPP
