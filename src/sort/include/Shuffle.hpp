#ifndef SHUFFLE_HPP
#define SHUFFLE_HPP

#include <iterator>
#include <random>

#include "Sort.hpp"

namespace algorithms {

/**
 * Shuffle method implementation class.
 */
class Shuffle : public Sort {
public:
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
            exchange(first + i, first + j);
        }
    }
};

} // namespace algorithms

#endif // SHUFFLE_HPP
