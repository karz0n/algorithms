#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Quick.hpp"

using namespace algorithms;

TEST(Quick, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
