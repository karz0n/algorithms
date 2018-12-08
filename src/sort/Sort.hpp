#ifndef SORT_HPP
#define SORT_HPP

#include <iterator>

namespace algorithms {

/**
 * Base class for all sort class.
 */
class Sort {
public:
    template <typename It>
    static void exchange(It from, It to)
    {
        using ValueType = typename std::iterator_traits<It>::value_type;

        if (from == to) {
            return;
        }

        ValueType temp = *from;
        *from = *to;
        *to = temp;
    }

    template <typename ForwardIt>
    static bool isAscending(ForwardIt first, ForwardIt last)
    {
        return isAscending(first, last, std::less<typename std::iterator_traits<ForwardIt>::value_type>{});
    }

    template <typename ForwardIt, typename Less>
    static bool isAscending(ForwardIt first, ForwardIt last, Less less)
    {
        while (first != last) {
            ForwardIt next = std::next(first);
            if (next == last) {
                break;
            }
            if (less(*next, *first)) {
                return false;
            }
            ++first;
        }
        return true;
    }
};

} // namespace algorithms

#endif // SORT_HPP
