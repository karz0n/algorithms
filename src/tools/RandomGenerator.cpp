#include "RandomGenerator.hpp"

#include <random>
#include <limits>

namespace algorithms {

const long RandomGenerator::MIN_VALUE = std::numeric_limits<long>::min();
const long RandomGenerator::MAX_VALUE = std::numeric_limits<long>::max();

Numbers
RandomGenerator::generate(std::size_t count, long from, long to)
{
    using Distribution = std::uniform_int_distribution<long>;

    if (count == 0) {
        return {};
    }

    if (to <= from) {
        return {};
    }

    std::random_device device;
    std::mt19937 g(device());
    Distribution d{from, to};

    Numbers numbers(count);
    for (std::size_t i = 0; i < count; ++i) {
        numbers[i] = d(g);
    }
    return numbers;
}

} // namespace algorithms
