#include "Sequence.hpp"

#include <limits>

namespace algorithms {

const long Sequence::MIN_NUMBER_VALUE = std::numeric_limits<long>::min();
const long Sequence::MAX_NUMBER_VALUE = std::numeric_limits<long>::max();

Numbers
Sequence::numbers(std::size_t count, long from /*= MIN_VALUE*/, long to /*= MAX_VALUE*/)
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
