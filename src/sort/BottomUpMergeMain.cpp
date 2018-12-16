#include <gtest/gtest.h>

#include <Tools.hpp>

#include "BottomUpMerge.hpp"

using namespace algorithms;

TEST(BottomUpMerge, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        BottomUpMerge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("BottomUpMerge - 1K", time);

    ASSERT_TRUE(BottomUpMerge::isAscending(numbers.begin(), numbers.end()));
}

TEST(BottomUpMerge, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        BottomUpMerge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("BottomUpMerge - 10K", time);

    ASSERT_TRUE(BottomUpMerge::isAscending(numbers.begin(), numbers.end()));
}

TEST(BottomUpMerge, Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        BottomUpMerge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("BottomUpMerge - 100K", time);

    ASSERT_TRUE(BottomUpMerge::isAscending(numbers.begin(), numbers.end()));
}
