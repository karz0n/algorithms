#ifndef BOTTOMUPMERGE_HPP
#define BOTTOMUPMERGE_HPP

#include <iterator>
#include <vector>
#include <functional>

namespace algorithms {

/**
 * Bottom-up merge sort method implementation class.
 *
 * Bottom-up merge sort is modification of merge sort. It doesn't contain
 * recursion.
 *
 * Properties:
 *   - Stable
 *   - Worst-case performance: N * lgN
 *   - Best-case performance: N * lgN
 *   - Average performance: N * lgN
 */
class BottomUpMerge {
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
        for (std::size_t step = 1; step < size; step += step) {
            for (std::size_t lo = 0; lo < size - step; lo += 2 * step) {
                merge(first, buffer.begin(), less, lo, lo + step - 1, std::min(lo + 2 * step - 1, size - 1));
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
