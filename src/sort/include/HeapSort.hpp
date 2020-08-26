#pragma once

#include <iterator>
#include <functional>
#include <utility>

namespace algorithms {

/**
 * Heap sort method implementation class.
 *
 * Properties:
 *   - Inplace
 *   - Worst-case performance: 2N x lgN / 2
 *   - Average performance: 2N x lgN / 2
 *   - Best-case performance: N x lgN
 *
 * Remark: No linear extra space and no quadratic time in worst case,
 *         but makes poor use of cache memory.
 */
class HeapSort {
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
        if (first >= last) {
            return;
        }

        std::size_t size = std::distance(first, last);
        for (std::size_t k = size / 2; k >= 1; --k) {
            sink(first, k, size, less);
        }

        while (size > 1) {
            std::swap(first[0], first[size - 1]);
            size--;
            sink(first, 1, size, less);
        }
    }

private:
    template<typename RandomIt, typename Less>
    static void
    sink(RandomIt input, std::size_t k, std::size_t size, Less less)
    {
        while (2 * k <= size) {
            std::size_t j = 2 * k;
            if (j < size && less(input[j - 1], input[j])) {
                j++;
            }
            if (less(input[k - 1], input[j - 1])) {
                std::swap(input[k - 1], input[j - 1]);
                k = j;
            }
            else
                break;
        }
    }
};

} // namespace algorithms
