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
    template <typename RandomAccessIt>
    static void shuffle(RandomAccessIt first, RandomAccessIt last)
    {
        using Distribution = std::uniform_int_distribution<std::size_t>;

        std::random_device device;
        std::mt19937 g(device());
        Distribution d;

        std::size_t l = std::distance(first, last);
        for (std::size_t i = 0; i < l; ++i) {
            std::size_t r = d(g, Distribution::param_type{0, i});
            exchange(first + i, first + r);
        }
    }
};

} // namespace algorithms

#endif // SHUFFLE_HPP
