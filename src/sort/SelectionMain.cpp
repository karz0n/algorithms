#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Selection.hpp"

using namespace algorithms;

TEST(Selection, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    Selection::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Selection, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    Selection::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Selection, DISABLED_Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    Selection::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
