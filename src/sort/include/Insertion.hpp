#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <iterator>
#include <algorithm>
#include <functional>

namespace algorithms {

/**
 * Insertion sort method implementation class.
 *
 * Properties:
 *   - Stable
 *   - Inplace
 *   - Worst-case performance: N^2 / 2
 *   - Average performance: N^2 / 4
 *   - Best-case performance: N
 *
 * Remark: Use for small N or partially ordered.
 */
class Insertion {
public:
    template<typename BidirectionalIt>
    static void sort(BidirectionalIt first, BidirectionalIt last)
    {
        using T = typename std::iterator_traits<BidirectionalIt>::value_type;

        sort(first, last, std::less<T>{});
    }

    template<typename BidirectionalIt, typename Less>
    static void sort(BidirectionalIt first, BidirectionalIt last, Less less)
    {
        if (first >= last) {
            return;
        }

        for (auto it = std::next(first); it != last; ++it) {
            for (auto c = it; c != first;) {
                auto p = std::prev(c);
                if (less(*c, *p)) {
                    std::iter_swap(c, p);
                    c = p;
                }
                else {
                    break;
                }
            }
        }
    }
};

} // namespace algorithms

#endif // INSERTION_HPP
