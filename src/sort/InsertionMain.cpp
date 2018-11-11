#include <gtest/gtest.h>

#include "Insertion.hpp"

using namespace algorithms;

TEST(Sort, Insertion)
{
    std::vector<int> numbers{ 4, 1, 5, 0, 10 };
    Insertion::sort(numbers.begin(), numbers.end());
    ASSERT_TRUE(Insertion::isAscending(numbers.begin(), numbers.end()));

    std::vector<char> chars{ 'B', 'A', 'C', 'F', 'L' };
    Insertion::sort(chars.begin(), chars.end());
    ASSERT_TRUE(Insertion::isAscending(chars.begin(), chars.end()));

    std::vector<std::string> strings{ "About", "New", "Text", "End", "Begin" };
    Insertion::sort(strings.begin(), strings.end());
    ASSERT_TRUE(Insertion::isAscending(strings.begin(), strings.end()));
}
