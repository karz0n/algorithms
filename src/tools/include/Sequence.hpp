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

public:
    template<typename T>
    static Numbers<T> numbers(std::size_t count, T from = MIN_NUMBER_VALUE<T>, T to = MAX_NUMBER_VALUE<T>)
    {
        static_assert(std::is_integral_v<T> || std::is_floating_point_v<T>, "Unsupported type");

        if constexpr (std::is_integral_v<T>) {
            return numbers(count, from, to, std::uniform_int_distribution<T>{from, to});
        }
        else {
            return numbers(count, from, to, std::uniform_real_distribution<T>{from, to});
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
        using D = std::uniform_int_distribution<std::size_t>;

        std::random_device device;
        std::mt19937 g(device());
        D d;

        std::size_t size = std::distance(first, last);
        for (std::size_t i = 0; i < size; ++i) {
            std::size_t j = d(g, D::param_type{0, i});
            std::iter_swap(first + i, first + j);
        }
    }

    template<typename ForwardIt>
    static bool isAscending(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::less<T>{});
    }

    template<typename ForwardIt>
    static bool isDescending(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::greater<T>{});
    }

    template<typename ForwardIt, typename Compare>
    static bool isOrdered(ForwardIt first, ForwardIt last, Compare compare)
    {
        for (; first != last; ++first) {
            ForwardIt next = std::next(first);
            if (next == last) {
                return true;
            }
            if (compare(*next, *first)) {
                return false;
            }
        }
        return true;
    }
};

} // namespace algorithms
