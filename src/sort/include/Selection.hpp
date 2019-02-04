#ifndef SELECTION_HPP
#define SELECTION_HPP

#include <iterator>
#include <algorithm>
#include <functional>

namespace algorithms {

/**
 * Selection sort method implementation class.
 *
 * Properties:
 *   + Not stable
 *   + Worst-case performance: О(n2) comparisons, О(n) swaps
 *   + Best-case performance: О(n2) comparisons, О(n) swaps
 *   + Average performance: О(n2) comparisons, О(n) swaps
 *
 * [selection-sort](https://www.toptal.com/developers/sorting-algorithms/selection-sort)
 */
class Selection {
public:
    template <typename ForwardIt>
    static void sort(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        sort(first, last, std::less<T>{});
    }

    template <typename ForwardIt, typename Less>
    static void sort(ForwardIt first, ForwardIt last, Less less)
    {
        for (; first != last; ++first) {
            ForwardIt min = first;
            for (auto it = std::next(first); it != last; ++it) {
                if (less(*it, *min)) {
                    min = it;
                }
            }
            std::iter_swap(min, first);
        }
    }
};

} // namespace algorithms

#endif // SELECTION_HPP
