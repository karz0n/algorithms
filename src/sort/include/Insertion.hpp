#ifndef INSERTION_HPP
#define INSERTION_HPP

#include <iterator>

#include "Sort.hpp"

namespace algorithms {

/**
 * Insertion sort method implementation class.
 *
 * Properties:
 *   + Stable
 *   + Worst-case performance: О(n2) comparisons and swaps
 *   + Best-case performance: O(n) comparisons, O(1) swaps
 *   + Average performance: О(n2) comparisons and swaps
 *
 * [insertion-sort](https://www.toptal.com/developers/sorting-algorithms/insertion-sort)
 */
class Insertion : public Sort {
public:
    template <typename BidirectionalIt>
    static void sort(BidirectionalIt first, BidirectionalIt last)
    {
        sort(first, last, std::less<typename std::iterator_traits<BidirectionalIt>::value_type>{});
    }

    template <typename BidirectionalIt, typename Less>
    static void sort(BidirectionalIt first, BidirectionalIt last, Less less)
    {
        if (first == last) {
            return;
        }

        for (auto it1 = std::next(first); it1 != last; ++it1) {
            for (auto it2 = it1; it2 != first;) {
                auto left = std::prev(it2);
                if (less(*it2, *left)) {
                    exchange(it2, left);
                    it2 = left;
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
