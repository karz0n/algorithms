#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Shell.hpp"

using namespace algorithms;

TEST(ShellTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    Shell::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
