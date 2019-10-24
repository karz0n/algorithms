#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Shell.hpp"

using namespace algorithms;

TEST(ShellTest, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
