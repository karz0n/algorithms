#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <vector>

namespace algorithms {

/**
 *
 */
using Numbers = std::vector<long>;

/**
 *
 */
class RandomGenerator
{
public:
    static const long MIN_VALUE;
    static const long MAX_VALUE;

    /**
     *
     * @param count
     * @param from
     * @param to
     *
     * @return
     */
    static Numbers generate(std::size_t count, long from = MIN_VALUE, long to = MAX_VALUE);

};

} // namespace algorithms

#endif // RANDOMGENERATOR_HPP
