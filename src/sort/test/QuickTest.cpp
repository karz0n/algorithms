#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Quick.hpp"

using namespace algorithms;

TEST(QuickTest, Sort1K)
{
    auto numbers = Sequence::numbers<int>(1000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(QuickTest, Sort10K)
{
    auto numbers = Sequence::numbers<int>(10000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}

TEST(QuickTest, Sort100K)
{
    auto numbers = Sequence::numbers<int>(100000);

    Quick::sort(numbers.begin(), numbers.end());

    ASSERT_TRUE(Sequence::isOrdered(numbers.begin(), numbers.end()));
}
