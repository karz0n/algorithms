#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "HeapSort.hpp"

using namespace algorithms;

TEST(HeapSortTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    HeapSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(HeapSortTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    HeapSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(HeapSortTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    HeapSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
