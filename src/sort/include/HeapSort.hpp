#pragma once

#include <functional>
#include <iterator>
#include <utility>
#include <concepts>

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
    template<std::random_access_iterator It>
    static void
    sort(It first, It last)
    {
        using T = typename std::iterator_traits<It>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<std::random_access_iterator It,
             std::predicate<typename std::iterator_traits<It>::value_type,
                            typename std::iterator_traits<It>::value_type> Compare>
    static void
    sort(It first, It last, Compare compare)
    {
        if (first >= last) {
            return;
        }

        std::size_t size = std::distance(first, last);
        for (std::size_t k = size / 2; k >= 1; --k) {
            sink(first, k, size, compare);
        }

        while (size > 1) {
            std::swap(first[0], first[size - 1]);
            size--;
            sink(first, 1, size, compare);
        }
    }

private:
    template<typename It, typename Compare>
    static void
    sink(It input, std::size_t k, std::size_t size, Compare compare)
    {
        while (2 * k <= size) {
            std::size_t j = 2 * k;
            if (j < size && compare(input[j - 1], input[j])) {
                j++;
            }
            if (compare(input[k - 1], input[j - 1])) {
                std::swap(input[k - 1], input[j - 1]);
                k = j;
            }
            else {
                break;
            }
        }
    }
};

} // namespace algorithms
