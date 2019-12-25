#pragma once

#include <iterator>
#include <algorithm>
#include <functional>
#include <random>
#include <limits>

namespace algorithms {

/** The list of real numbers */
template<typename T>
using Numbers = std::vector<T>;

class Sequence {
public:
    template<typename T>
    static constexpr T MIN_NUMBER_VALUE = std::numeric_limits<T>::min();
    template<typename T>
    static constexpr T MAX_NUMBER_VALUE = std::numeric_limits<T>::max();

    template<typename T>
    static Numbers<T> numbers(std::size_t count, T from = MIN_NUMBER_VALUE<T>, T to = MAX_NUMBER_VALUE<T>)
    {
        if constexpr (std::is_integral_v<T>) {
            return numbers(count, from, to, std::uniform_int_distribution<T>{});
        }
        else {
            return numbers(count, from, to, std::uniform_real_distribution<T>{});
        }
    }

    template<typename T, typename D>
    static Numbers<T> numbers(std::size_t count, T from, T to, D distribution)
    {
        if (count == 0) {
            return {};
        }

        if (to <= from) {
            return {};
        }

        std::random_device device;
        std::mt19937 g(device());

        Numbers<T> numbers(count);
        for (std::size_t i = 0; i < count; ++i) {
            numbers[i] = distribution(g);
        }
        return numbers;
    }

    template<typename RandomIt>
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

    template<typename ForwardIt>
    static bool isOrdered(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::less<T>{});
    }

    template<typename ForwardIt, typename Less>
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
