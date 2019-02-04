#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <iterator>
#include <algorithm>
#include <functional>
#include <random>

namespace algorithms {

using Numbers = std::vector<long>;

class Sequence {
public:
    static const long MIN_NUMBER_VALUE;
    static const long MAX_NUMBER_VALUE;

    static Numbers numbers(std::size_t count, long from = MIN_NUMBER_VALUE, long to = MAX_NUMBER_VALUE);

    template <typename RandomIt>
    static void shuffle(RandomIt first, RandomIt last)
    {
        using Distribution = std::uniform_int_distribution<std::size_t>;

        std::random_device device;
        std::mt19937 g(device());
        Distribution d;

        std::size_t size = std::distance(first, last);
        for (std::size_t i = 0; i < size; ++i) {
            std::size_t j = d(g, Distribution::param_type{0, i});
            std::iter_swap(first + i, first + j);
        }
    }

    template <typename ForwardIt>
    static bool isOrdered(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::less<T>{});
    }

    template <typename ForwardIt, typename Less>
    static bool isOrdered(ForwardIt first, ForwardIt last, Less less)
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

#endif // SEQUENCE_HPP
