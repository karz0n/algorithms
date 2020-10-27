#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "MergeSort.hpp"

using namespace algorithms;

TEST(MergeTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    MergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(MergeTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    MergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(MergeTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    MergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
