#include <gtest/gtest.h>

#include <Tools.hpp>

#include "Selection.hpp"

using namespace algorithms;

TEST(Selection, Sort1K)
{
    Numbers numbers = RandomGenerator::generate(1000);

    auto time = measure([&] () {
        Selection::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Selection - 1K", time);

    ASSERT_TRUE(Selection::isAscending(numbers.begin(), numbers.end()));
}

TEST(Selection, Sort10K)
{
    Numbers numbers = RandomGenerator::generate(10000);

    auto time = measure([&] () {
        Selection::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Selection - 10K", time);

    ASSERT_TRUE(Selection::isAscending(numbers.begin(), numbers.end()));
}

TEST(Selection, DISABLED_Sort100K)
{
    Numbers numbers = RandomGenerator::generate(100000);

    auto time = measure([&] () {
        Selection::sort(numbers.begin(), numbers.end());
    });
    printMeasure("Selection - 100K", time);

    ASSERT_TRUE(Selection::isAscending(numbers.begin(), numbers.end()));
}
