#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Quick.hpp"

using namespace algorithms;

TEST(Quick, Sort1K)
{
    Numbers numbers = Sequence::numbers(1000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort10K)
{
    Numbers numbers = Sequence::numbers(10000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort100K)
{
    Numbers numbers = Sequence::numbers(100000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(Quick, Select)
{
    Numbers numbers{0, -1, 15, 3, 7, 10, 1};

    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 0), -1);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 1), 0);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 2), 1);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 3), 3);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 4), 7);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 5), 10);
    ASSERT_EQ(Quick::select<int>(numbers.begin(), numbers.end(), 6), 15);
}
