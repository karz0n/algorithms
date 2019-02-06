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
 *   - Not stable
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: N^2 / 2
 *   - Best-case performance: N^2 / 2
 *
 * Remark: N exchanges.
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
