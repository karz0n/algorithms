#include <gtest/gtest.h>

#include <Tools.hpp>

#include "Quick.hpp"

using namespace algorithms;

TEST(Quick, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        Quick::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Quick - 1K", time);

    ASSERT_TRUE(Quick::isAscending(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        Quick::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Quick - 10K", time);

    ASSERT_TRUE(Quick::isAscending(numbers.begin(), numbers.end()));
}

TEST(Quick, Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        Quick::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Quick - 100K", time);

    ASSERT_TRUE(Quick::isAscending(numbers.begin(), numbers.end()));
}

