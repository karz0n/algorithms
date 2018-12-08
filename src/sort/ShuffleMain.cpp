#include <gtest/gtest.h>

#include "Shuffle.hpp"

using namespace algorithms;

TEST(Sort, Shuffle)
{
    std::vector<int> numbers{ 4, 1, 5, 0, 10 };
    Shuffle::shuffle(numbers.begin(), numbers.end());
}
