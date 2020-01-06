#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Merge.hpp"

using namespace algorithms;

TEST(MergeTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(MergeTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(MergeTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    Merge::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
