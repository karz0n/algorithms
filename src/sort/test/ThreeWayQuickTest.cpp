#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "ThreeWayQuick.hpp"

using namespace algorithms;

TEST(ThreeWayQuickTest, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
