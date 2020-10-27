#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "SelectionSort.hpp"

using namespace algorithms;

TEST(SelectionTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    SelectionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(SelectionTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    SelectionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(SelectionTest, DISABLED_Sort100K /* disabled because test takes too much time */)
{
    auto numbers = Sequence::numbers<int>(100000);

    SelectionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
