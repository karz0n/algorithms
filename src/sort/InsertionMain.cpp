#include <gtest/gtest.h>

#include <Tools.hpp>

#include "Insertion.hpp"

using namespace algorithms;

TEST(Insertion, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        Insertion::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Selection - 1K", time);

    ASSERT_TRUE(Insertion::isAscending(numbers.begin(), numbers.end()));
}

TEST(Insertion, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        Insertion::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Insertion - 10K", time);

    ASSERT_TRUE(Insertion::isAscending(numbers.begin(), numbers.end()));
}

TEST(Insertion, DISABLED_Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        Insertion::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Insertion - 100K", time);

    ASSERT_TRUE(Insertion::isAscending(numbers.begin(), numbers.end()));
}
