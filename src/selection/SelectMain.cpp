#include <gtest/gtest.h>

#include <Sequence.hpp>

#include "Select.hpp"

using namespace algorithms;

TEST(Quick, Select)
{
    Numbers numbers{0, -1, 15, 3, 7, 10, 1};

    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 0), -1);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 1), 0);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 2), 1);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 3), 3);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 4), 7);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 5), 10);
    ASSERT_EQ(Select::get<int>(numbers.begin(), numbers.end(), 6), 15);
}
