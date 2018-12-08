#include <gtest/gtest.h>

#include <Tools.hpp>

#include "Merge.hpp"

using namespace algorithms;

TEST(Merge, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        Merge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Merge - 1K", time);

    ASSERT_TRUE(Merge::isAscending(numbers.begin(), numbers.end()));
}

TEST(Merge, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        Merge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Merge - 10K", time);

    ASSERT_TRUE(Merge::isAscending(numbers.begin(), numbers.end()));
}

TEST(Merge, Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        Merge::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Merge - 100K", time);

    ASSERT_TRUE(Merge::isAscending(numbers.begin(), numbers.end()));
}
