#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "ThreeWayQuick.hpp"

using namespace algorithms;

TEST(ThreeWayQuickTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    ThreeWayQuick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
