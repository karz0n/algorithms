#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "QuickSort.hpp"

using namespace algorithms;

TEST(QuickTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    QuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(QuickTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    QuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(QuickTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    QuickSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
