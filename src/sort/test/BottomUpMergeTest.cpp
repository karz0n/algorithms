#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "BottomUpMerge.hpp"

using namespace algorithms;

TEST(BottomUpMergeTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(BottomUpMergeTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(BottomUpMergeTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    BottomUpMerge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
