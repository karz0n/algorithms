#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "InsertionSort.hpp"

using namespace algorithms;

TEST(InsertionTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    InsertionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(InsertionTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    InsertionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(InsertionTest, DISABLED_Sort100K /* disabled because test takes too much time */)
{
    auto numbers = Sequence::numbers<int>(100000);

    InsertionSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
