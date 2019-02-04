#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "BottomUpMerge.hpp"

using namespace algorithms;

TEST(BottomUpMerge, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(BottomUpMerge, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(BottomUpMerge, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
