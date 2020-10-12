#pragma once

#include <functional>
#include <vector>

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
    template<typename RandomIt>
    static void
    sort(RandomIt first, RandomIt last)
    {
        using T = typename std::iterator_traits<RandomIt>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<typename RandomIt, typename Less>
    static void
    sort(RandomIt first, RandomIt last, Less less)
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
    template<typename RandomIt, typename Less>
    static void
    sort(RandomIt input, RandomIt output, Less less, std::size_t lo, std::size_t hi)
    {
        if (hi <= lo) {
            return;
        }

        // take middle of array
        std::size_t mid = lo + (hi - lo) / 2;

        // sort two parts
        sort(input, output, less, lo, mid);
        sort(input, output, less, mid + 1, hi);

        // merge two sorted parts
        merge(input, output, less, lo, mid, hi);
    }

    template<typename RandomIt, typename Less>
    static void
    merge(
        RandomIt input, RandomIt output, Less less, std::size_t lo, std::size_t mid, std::size_t hi)
    {
        // copy elements to buffer
        for (std::size_t k = lo; k <= hi; ++k) {
            output[k] = input[k];
        }

        // merge two parts
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
