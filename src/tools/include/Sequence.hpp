#pragma once

#include <iterator>
#include <algorithm>
#include <functional>
#include <random>
#include <limits>
#include <tuple>

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
    /**
     * Generates numbers.
     *
     * @param count - the count of numbers
     * @param from - the min value of generated numbers
     * @param to - the max value of generated numbers
     *
     * @return the list of generated numbers
     */
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

    /**
     * Generates numbers.
     *
     * @param count - the count of numbers
     * @param from - the min value of generated numbers
     * @param to - the max value of generated numbers
     * @param d - the distribution object
     *
     * @return the list of generated numbers
     */
    template<typename T, typename D>
    static Numbers<T> numbers(std::size_t count, T from, T to, D d)
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
            numbers[i] = d(g);
        }
        return numbers;
    }

    /**
     * Shuffles the sequence.
     *
     * @param first - the iterator to the first position of sequence
     * @param last - the iterator to the last position of sequence
     */
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

    /**
     * Checks if the sequence is sorted in ascending order.
     *
     * @param first - the iterator to the first position of sequence
     * @param last - the iterator to the last position of sequence
     *
     * @return \c true if sequence sorted in ascending order, \c false otherwise
     */
    template<typename ForwardIt>
    static bool isAscending(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::less<T>{});
    }

    /**
     * Checks if the sequence is sorted in descending order.
     *
     * @param first - the iterator to the first position of sequence
     * @param last - the iterator to the last position of sequence
     *
     * @return \c true if sequence sorted in descending order, \c false otherwise
     */
    template<typename ForwardIt>
    static bool isDescending(ForwardIt first, ForwardIt last)
    {
        using T = typename std::iterator_traits<ForwardIt>::value_type;

        return isOrdered(first, last, std::greater<T>{});
    }

    /**
     * Checks if the sequence is sorted in descending order.
     *
     * @param first - the iterator to the first position of sequence
     * @param last - the iterator to the last position of sequence
     * @param p - the predicate used to compare two values
     */
    template<typename ForwardIt, typename BinaryPredicate>
    static bool isOrdered(ForwardIt first, ForwardIt last, BinaryPredicate p)
    {
        for (; first != last; ++first) {
            ForwardIt next = std::next(first);
            if (next == last) {
                return true;
            }
            if (p(*next, *first)) {
                return false;
            }
        }
        return true;
    }

    /**
     * Partitions the sequence into three parts:
     *  + first part containes values less than pivot element
     *  + second part contains values equal to pivot element
     *  + third part contains values greater than pivot element
     *
     * First element in sequence is choose as pivot element.
     *
     * @param first - the iterator to the first position of sequence
     * @param last - the iterator to the last position of sequence
     * @param p - the predicate used to compare two values
     *
     * @return the pair of iteratos, where first points to the first not less than pivot
     *         and the second points to the first greater than pivot element
     */
    template<typename BidirIt, typename BinaryPredicate>
    static std::tuple<BidirIt, BidirIt> partition(BidirIt first, BidirIt last, BinaryPredicate p)
    {
        if (first >= last) {
            return std::make_tuple(last, last);
        }

        BidirIt lt = first;
        BidirIt gt = std::prev(last);
        BidirIt it = std::next(first);

        while (it <= gt) {
            int c = std::invoke(p, *it, *lt);
            if (c < 0) {
                std::iter_swap(it++, lt++);
                continue;
            }
            if (c > 0) {
                std::iter_swap(it, gt--);
                continue;
            }
            it++;
        }

        return std::make_tuple(lt, ++gt);
    }
};

} // namespace algorithms
