#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "ThreeWayQuickSort.hpp"

using namespace algorithms;

TEST(ThreeWayQuickTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    ThreeWayQuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    ThreeWayQuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(ThreeWayQuickTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    ThreeWayQuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
