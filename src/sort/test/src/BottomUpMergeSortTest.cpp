#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "BottomUpMergeSort.hpp"

using namespace algorithms;

TEST(BottomUpMergeTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    BottomUpMergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(BottomUpMergeTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    BottomUpMergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(BottomUpMergeTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    BottomUpMergeSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
