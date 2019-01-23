#ifndef SHELL_HPP
#define SHELL_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {

/**
 * Shell sort method implementation class.
 *
 * Properties:
 *   + Not stable
 *   + Worst-case performance: O(n2) (worst known gap sequence)
 *   + Best-case performance: O(n log2n) (best known gap sequence)
 *   + Average performance: O(n log n)
 *
 * [shell-sort](https://www.toptal.com/developers/sorting-algorithms/shell-sort)
 */
class Shell : public Sort {
public:
    template <typename RandomAccessIt>
    static void sort(RandomAccessIt first, RandomAccessIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<RandomAccessIt>::value_type>{});
    }

    template <typename RandomAccessIt, typename Less>
    static void sort(RandomAccessIt first, RandomAccessIt last, Less less)
    {
        // Get number of elements.
        //
        std::size_t count = std::distance(first, last);

        // Obtain optimal first step.
        //
        std::size_t h = 1;
        while (h < count / 3) {
            h = 3 * h + 1;
        }

        // First cycle: iterate size of step beginning from optimal and
        // reduce step by 1/3 in each iteration.
        //
        while (h >= 1) {
            // Sort interleaved sequence array using insertion sort.
            //
            for (std::size_t i = h; i < count; ++i) {
                // Sort items by h (not by one).
                //
                for (std::size_t j = i; j >= h; j -= h) {
                    if (less(first[j], first[j - h])) {
                        exchange(first + j, first + j - h);
                    }
                    else {
                        break;
                    }
                }
            }

            h /= 3;
        }
    }
};

} // namespace algorithms

#endif // SHELL_HPP
