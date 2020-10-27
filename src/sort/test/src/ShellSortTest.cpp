#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "ShellSort.hpp"

using namespace algorithms;

TEST(ShellTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    ShellSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    ShellSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}

TEST(ShellTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    ShellSort::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isAscending(numbers.begin(), numbers.end()));
}
