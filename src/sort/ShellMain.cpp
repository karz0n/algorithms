#include <gtest/gtest.h>

#include <Tools.hpp>

#include "Shell.hpp"

using namespace algorithms;

TEST(Shell, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        Shell::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Shell - 1K", time);

    ASSERT_TRUE(Shell::isAscending(numbers.begin(), numbers.end()));
}

TEST(Shell, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        Shell::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Shell - 10K", time);

    ASSERT_TRUE(Shell::isAscending(numbers.begin(), numbers.end()));
}

TEST(Shell, Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        Shell::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Shell - 100K", time);

    ASSERT_TRUE(Shell::isAscending(numbers.begin(), numbers.end()));
}
