#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Merge.hpp"

using namespace algorithms;

TEST(Merge, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Merge, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Merge, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
